namespace IR {

    IR_BEGIN_OBJECT(InfinitRightDrawingObject)
        public:
        InfinitRightDrawingObject(const IRUUID& uuid = IRUUID().CreateNew());
        private:
        IR_DEFINE_PROPERTY(Count, u32);
    IR_END_OBJECT

}