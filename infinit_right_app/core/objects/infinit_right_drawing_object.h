namespace IR {

    IR_OBJECT_NEW(InfinitRightDrawingObject)
        public:
        InfinitRightDrawingObject(const IRUUID& uuid = IRUUID().CreateNew());
        private:
        IR_DEFINE_PROPERTY(Count, u32);
    IR_END_OBJECT

}