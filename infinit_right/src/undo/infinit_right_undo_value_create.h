#pragma once

namespace IR {

	class InfinitRightUndoValueCreate : public InfinitRightUndoValue
	{
	public:
		InfinitRightUndoValueCreate(const IRUUID& objectUuid, const IRJson& object);
		~InfinitRightUndoValueCreate();
	private:
		IRJson		fJSObject;
	public:
		virtual void Undo();
		virtual void Redo();

		virtual void WriteCallbackJson(IRJson& json);
	};

}