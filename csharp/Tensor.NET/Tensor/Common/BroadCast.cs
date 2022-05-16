using Tensornet.Common;

namespace Tensornet{
    public partial class Tensor<T>{
        public Tensor<T> Broadcast(Span<int> targetShape){
            return new Tensor<T>(this.TMemory, this.TLayout.Broadcast(new TensorShape(targetShape)));
        }

        public Tensor<T> Broadcast(TensorShape targetShape){
            return new Tensor<T>(this.TMemory, this.TLayout.Broadcast(targetShape));
        }

        public Tensor<T> Broadcast(int[] targetShape){
            return new Tensor<T>(this.TMemory, this.TLayout.Broadcast(new TensorShape(targetShape)));
        }
        public virtual void BroadcastTo(TensorShape targetShape){
            TLayout.BroadcastInplace(targetShape);
        }
        public virtual void BroadcastTo(int[] targetShape){
            TLayout.BroadcastInplace(new TensorShape(targetShape));
        }
    }
}