#pragma once

namespace IR {

	class InfinitRightDrawing : public InfinitRightObject
	{
	public:
		InfinitRightDrawing(const IRString& name);
		~InfinitRightDrawing();
	private:
		TObjectMap				fObjects;
	public:
		InfinitRightObject*			CreateNewObject(u32 objectType, InfinitRightObject* parent = nullptr, const IRUUID& uuid = IRUUID().CreateNew());
		void						DeleteObject(const IRUUID& uuid);

		InfinitRightObject*			GetObjectByUuid(const IRUUID& uuid);
		TObjectList					GetObjects() const;
	};

}