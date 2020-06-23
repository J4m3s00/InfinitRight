namespace IR {

    IR_OBJECT_NEW(InfinitRightDrawingObject)
        public:
        InfinitRightDrawingObject(const IRUUID& uuid = IRUUID().CreateNew());
        private:
        IR_DEFINE_PROPERTY(Count, u32);
        IR_DEFINE_PROPERTY(Selected, bool);
    IR_END_OBJECT

    IR_OBJECT_SUB(InfinitRightSymbol, InfinitRightDrawingObject)
        public:
        InfinitRightSymbol(const IRUUID& uuid = IRUUID().CreateNew());
    IR_END_OBJECT

}