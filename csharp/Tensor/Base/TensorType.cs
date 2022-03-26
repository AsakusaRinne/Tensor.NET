using Numnet.Native;

namespace Numnet.Base{
    internal sealed class TensorTypeInfo
    {
        private static readonly Dictionary<Type, TensorTypeInfo> _typeInfoMap;
        private static readonly Dictionary<DType, Type> _dtypeMap;
        public readonly DType _dtype;
        public readonly int _size;
        static TensorTypeInfo(){
            _typeInfoMap = new Dictionary<Type, TensorTypeInfo>()
            {
                { typeof(float), new TensorTypeInfo( DType.Float32, sizeof(float)) },
                // { typeof(byte), new TensorTypeInfo( DType.UInt8, sizeof(byte)) },
                // { typeof(sbyte), new TensorTypeInfo( DType.Int8, sizeof(sbyte)) },
                // { typeof(ushort), new TensorTypeInfo( DType.UInt16, sizeof(ushort)) },
                // { typeof(short), new TensorTypeInfo( DType.Int16, sizeof(short)) },
                { typeof(int), new TensorTypeInfo( DType.Int32, sizeof(int)) },
                // { typeof(long), new TensorTypeInfo( DType.Int64, sizeof(long)) },
                // { typeof(string), new TensorTypeInfo( DType.String, -1) },
                { typeof(bool), new TensorTypeInfo( DType.Bool, sizeof(bool)) },
                { typeof(double), new TensorTypeInfo( DType.Float64, sizeof(double)) },
                // { typeof(uint), new TensorTypeInfo( DType.UInt32, sizeof(uint)) },
                // { typeof(ulong), new TensorTypeInfo( DType.UInt64, sizeof(ulong)) },
            };
            _dtypeMap = _typeInfoMap.ToDictionary(k => k.Value._dtype, v => v.Key);
        }
        public TensorTypeInfo(DType dtype, int size){
            _dtype = dtype;
            _size = size;
        }
        public static TensorTypeInfo GetTypeInfo(Type type){
            TensorTypeInfo res;
            if(!_typeInfoMap.TryGetValue(type, out res)){
                throw new UnsopportedTypeException();
            }
            return res;
        }
        public static Type GetTypeInfo(DType type){
            Type res;
            if(!_dtypeMap.TryGetValue(type, out res)){
                throw new UnsopportedTypeException();
            }
            return res;
        }
    }
}