using Tensornet.Native;
using System.Text;
using Tensornet.Exceptions;

namespace Tensornet{
    public class TensorShape{
        public static readonly int MAX_NDIM = 4;
        public int[] Shape { get; internal set; } = new int[MAX_NDIM];
        public int NDim{ get; internal set; }
        public TensorShape(params int[] shape){
            if(shape.Length > MAX_NDIM){
                throw new DimExceedException(shape.Length);
            }
            NDim = shape.Length;
            for (int i = 0; i < NDim; i++){
                Shape[i] = shape[i];
            }
        }
        public TensorShape(Span<int> shape){
            if(shape.Length > MAX_NDIM){
                throw new DimExceedException(shape.Length);
            }
            NDim = shape.Length;
            for (int i = 0; i < NDim; i++){
                Shape[i] = shape[i];
            }
        }
        public TensorShape(IEnumerable<int> shape){
            if(shape.Count() > MAX_NDIM){
                throw new DimExceedException(shape.Count());
            }
            NDim = shape.Count();
            int i = 0;
            foreach(var value in shape){
                Shape[i] = value;
                i++;
            }
        }
        public TensorShape(TensorShape rhs){
            NDim = rhs.NDim;
            rhs.Shape.CopyTo(Shape.AsSpan());
        }
        internal TensorShape(){
            NDim = 0;
        }
        public bool IsScalar(){
            return NDim == 1 && Shape[0] == 1;
        }
        public bool IsSameShape(TensorShape rhs){
            if(NDim != rhs.NDim) return false;
            for (int i = 0; i < NDim; i++){
                if(Shape[i] != rhs.Shape[i]) return false;
            }
            return true;
        }
        public int TotalElemCount(){
            if(NDim == 0){
                return 0;
            }
            int res = 1;
            for (int i = 0; i < NDim; i++){
                res *= Shape[i];
            }
            return res;
        }

        public static implicit operator TensorShape(int[] shape){
            return new TensorShape(shape);
        }

        public static implicit operator TensorShape(Span<int> shape){
            return new TensorShape(shape);
        }

        public override string ToString()
        {
            return $"TensorShape({GetInfoString()})";
        }

        internal string GetInfoString(){
            StringBuilder r = new StringBuilder();
            if (NDim == 0) {
                r.Append(" Scalar");
            } else {
                r.Append("shape = {");
                for (int i = 0; i < NDim; i++) {
                    r.Append(Shape[i]);
                    if (i != NDim - 1) r.Append(", ");
                }
                r.Append("}");
            }
            return r.ToString();
        }
    }
    public sealed partial class TensorLayout:TensorShape
    {
        public DType DType { get; internal set; }
        /// <summary>
        /// The offset here is by mean of element, while the offset in c++ means the offset of bytes.
        /// So when calling native apis, a conversion needs to be done to interop.
        /// </summary>
        public int Offset{ get; internal set; }
        public int[] Stride { get; internal set; } = new int[MAX_NDIM];
        public TensorLayout()
        {
            DType = DType.Invalid;
            NDim = 0;
            Offset = 0;
        }
        public TensorLayout(Span<int> shape, DType dtype):base(shape)
        {
            DType = dtype;
            Offset = 0;
            InitContiguousLayout();
        }

        public TensorLayout(int[] shape, DType dtype):base(shape)
        {
            DType = dtype;
            Offset = 0;
            InitContiguousLayout();
        }

        public TensorLayout(TensorShape shape, DType dtype):base(shape)
        {
            DType = dtype;
            Offset = 0;
            InitContiguousLayout();
        }

        public TensorLayout(TensorLayout rhs, bool initContiguous = false){
            DType = rhs.DType;
            Offset = rhs.Offset;
            NDim = rhs.NDim;
            rhs.Shape.CopyTo(Shape.AsSpan());
            if(!initContiguous){
                rhs.Stride.CopyTo(Stride.AsSpan());
            }
            else{
                InitContiguousLayout();
            }
        }

        public bool IsSameLayout(TensorLayout rhs){
            for (int i = 0; i < NDim; i++){
                if(Stride[i] != rhs.Stride[i]) return false;
            }
            return DType == rhs.DType && IsSameShape(rhs);
        }

        public override string ToString()
        {
            return $"TensorLayout({GetInfoString()})";
        }

        internal new string GetInfoString(){
            StringBuilder r = new StringBuilder();
            if (NDim == 0) {
                r.Append(" Scalar");
            } else {
                r.Append("shape = {");
                for (int i = 0; i < NDim; i++) {
                    r.Append(Shape[i]);
                    if (i != NDim - 1) r.Append(", ");
                }
                r.Append("}");
            }
            r.Append(", dtype = ");
            r.Append(DType);
            return r.ToString();
        }

        internal void InitContiguousLayout()
        {
            int s = 1;
            for (int i = 0; i < NDim; i++)
            {
                Stride[NDim - i - 1] = s;
                s *= Shape[NDim - i - 1];
            }
        }

        public bool IsContiguous(){
            int expected = 1;
            for (int i = 0; i < NDim; ++i) {
                if (Shape[NDim - i - 1] != 1 && Stride[NDim - i - 1] != expected)
                    return false;
                expected *= Shape[NDim - i - 1];
            }
            // empty tensors are not contiguous
            return expected != 0;
        }

        internal TensorLayout Reshape(TensorShape targetShape, bool isImage){
            int targetNDim = targetShape.NDim;
            if(targetNDim <= 0){
                throw new InvalidShapeException(targetShape.Shape, "Reshape");
            }

            if(this.TotalElemCount() != targetShape.TotalElemCount()){
                throw new InvalidShapeException($"Number of elements does not match in reshape: src = {this.TotalElemCount()}, dst = {targetShape.TotalElemCount()}.");
            }

            TensorLayout res = new TensorLayout(targetShape, this.DType);
            // Maybe the process here is not correct when dealing with image.
            // Because the shape is not converted into contiguous before the process.
            if (isImage) {
                if(this.NDim < 2){
                    throw new InvalidOperationException("The tensor to reshape is not an image.");
                }
                else if(targetNDim < 2){
                    throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) is not an invalid shape for image.");
                }
                else if(this.Shape[NDim - 1] != targetShape.Shape[targetNDim - 2] || this.Shape[NDim - 2] != targetShape.Shape[targetNDim - 1]){
                    throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) does not match the current shape({string.Join(',', this.Shape)}) as an image.");
                }
                else if(NDim != targetNDim){
                    throw new NotImplementedException("Cuurently only the reverse of width and height of image is supported.");
                }
                for (int i = 0; i < this.NDim - 2; i++) {
                    if (targetShape.Shape[i] != this.Shape[i]) {
                        throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) does not match the current shape({string.Join(',', this.Shape)}) as an image to reshape.");
                    }
                }
                (res.Stride[NDim - 1], res.Stride[NDim - 2]) = (res.Stride[NDim - 2], res.Stride[NDim - 1]);
                return res;
            }

            var cont = CollapseContiguous();

            int sdim = 0, prod = 1, cont_sdim = 0;
            for (int i = 0; i < targetNDim; i++) {
                if(cont_sdim >= cont.NDim){
                    throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) does not match the current shape({string.Join(',', this.Shape)}) to reshape.");
                }
                prod *= res.Shape[i];
                if (prod > cont.Shape[cont_sdim])
                    throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) does not match the current shape({string.Join(',', this.Shape)}) to reshape.");

                if (prod == cont.Shape[cont_sdim] &&
                    (i + 1 >= targetNDim || targetShape.Shape[i + 1] != 1)) {
                    int s = cont.Stride[cont_sdim];
                    for (int j = i; j >= sdim; j--) {
                        res.Stride[j] = s;
                        s *= res.Shape[j];
                    }
                    cont_sdim++;
                    sdim = i + 1;
                    prod = 1;
                }
            }
            if(cont_sdim != cont.NDim) throw new InvalidShapeException($"The target shape({string.Join(',', targetShape)}) does not match the current shape({string.Join(',', this.Shape)}) to reshape.");

            return res;
        }

        internal TensorLayout CollapseContiguous() {
            if(NDim == 0){
                throw new InvalidShapeException($"The ndim of the tensor that try to collapse contiguously is 0.");
            }
            TensorLayout res = new TensorLayout(this);

            // remove all dims with shape 1
            for (int i = 0; i <= res.NDim - 1 && res.NDim >= 2; i++) {
                if (res.Shape[i] == 0) {
                    // empty tensor
                    res.NDim = 1;
                    res.Shape[0] = 0;
                    res.Stride[0] = 1;
                    return res;
                }
                if (res.Shape[i] == 1) res.RemoveAxisInplace(i);
            }

            if (res.NDim == 1) {
                if (res.Shape[0] <= 1) {
                    res.Stride[0] = 1;
                }
                return res;
            }

            if(res.NDim <= 0 || res.Shape[res.NDim - 1] <= 0){
                throw new InvalidShapeException(this.Shape, "CollapseContiguous");
            }
            for (int i = res.NDim - 2; i >= 0; i--) {
                if(res.Shape[i] <= 0){
                    throw new InvalidShapeException(this.Shape, "CollapseContiguous");
                }
                if (res.Stride[i] == res.Stride[i + 1] * res.Shape[i + 1]) {
                    res.Shape[i] *= res.Shape[i + 1];
                    res.Stride[i] = res.Stride[i + 1];
                    res.RemoveAxisInplace(i + 1);
                }
            }
            return res;
        }

        internal void RemoveAxisInplace(int axis) {
            if(NDim < 2){
                throw new InvalidShapeException($"Could not remove axis of a tensor with only {NDim} dims.");
            }
            else if(axis >= NDim){
                throw new InvalidArgumentException($"Axis to remove exceeds the NDim. Axis is {axis}, NDim is {NDim}.");
            }
            NDim--;
            for (int i = axis; i < NDim; i++) {
                Shape[i] = Shape[i + 1];
                Stride[i] = Stride[i + 1];
            }
        }

        internal TensorLayout RemoveAxis(int axis){
            var res = new TensorLayout(this);
            res.RemoveAxisInplace(axis);
            return res;
        }

        internal void RemoveAllDanglingAxisInplace(){
            for (int i = NDim - 1; i >= 0; i--){
                if(Shape[i] == 1 && NDim > 1){
                    RemoveAxisInplace(i);
                }
            }
        }

        internal void AddAxisInplace(int axis, int shape, int stride) {
            if(NDim + 1 > MAX_NDIM){
                throw new InvalidArgumentException($"can not add axis at {axis} (current ndim is {NDim}, MAX_NDIM is {MAX_NDIM})");
            }
            NDim++;
            for (int i = NDim- 1; i > axis; i--) {
                Shape[i] = Shape[i - 1];
                Stride[i] = Stride[i - 1];
            }
            Shape[axis] = shape;
            Stride[axis] = stride;
        }

        internal TensorLayout AddAxis(int axis, int shape, int stride){
            var res = new TensorLayout(this);
            res.AddAxisInplace(axis, shape, stride);
            return res;
        }

        internal bool CanBroadCastTo(TensorShape targetShape){
            int targetNDim = targetShape.NDim;
            if(targetNDim < NDim) return false;
            for (int i = 0; i < targetNDim; i++) {
                int cur_shape = i < NDim ? Shape[NDim - i - 1] : 1, cur_stride = i < NDim ? Stride[NDim - i - 1] : 0;
                if (targetShape.Shape[targetNDim - i - 1] != cur_shape && cur_shape != 1 && cur_stride != 0)
                    return false;
            }
            return true;
        }

        internal void BroadcastInplace(TensorShape targetShape){
            int targetNDim = targetShape.NDim;
            if(NDim <= 0 || targetNDim <= 0){
                throw new InvalidShapeException("Cannot broadcast (to) empty tensor shape");
            }

            if (IsScalar()) {
                NDim = targetNDim;
                for (int i = 0; i < targetNDim; i++) {
                    Shape[i] = targetShape.Shape[i];
                    Stride[i] = targetShape.Shape[i] == 1?1:0;
                }
                return;
            }

            if(targetNDim < NDim){
                throw new InvalidShapeException($"Dimension after broadcast is less than that before braodcast. ");
            }

            for (int i = 0; i < targetNDim; i++) {
                int targetIdx = targetNDim - i - 1;
                int cur_shape = i < NDim ? Shape[NDim - i - 1] : 1, cur_stride = i < NDim ? Stride[NDim - i - 1] : 0;
                if (targetShape.Shape[targetIdx] != cur_shape) {
                    if(cur_shape != 1 && cur_stride != 0){
                        throw new InvalidShapeException($"Broadcast on dim {NDim - i - 1} with shape not equal to 0 or 1.");
                    }
                    Shape[targetIdx] = targetShape.Shape[targetIdx];
                    Stride[targetIdx] = 0;
                } else {
                    Shape[targetIdx] = cur_shape;
                    Stride[targetIdx] = cur_stride;
                }
            }
            NDim = targetNDim;
        }

        internal TensorLayout Broadcast(TensorShape targetShape){
            TensorLayout res = new TensorLayout(this);
            res.BroadcastInplace(targetShape);
            return res;
        }
    }
    

}