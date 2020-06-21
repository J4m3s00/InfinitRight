#pragma once

namespace IR {

	class InfinitRightUndoValueCreate : public InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValueCreate(const IRUUID& objectUuid, const IRJson& object, const IRObjectId& objectId);
		virtual ~InfinitRightUndoValueCreate();
	private:
		IRJson		fJSObject;
	public:
		virtual void Undo();

		virtual void WriteCallbackJson(IRJson& json);
	};

}