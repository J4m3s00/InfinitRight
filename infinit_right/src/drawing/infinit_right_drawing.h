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
		InfinitRightObject*			CreateNewObject(const IRString& objectType, InfinitRightObject* parent = nullptr, const IRUUID& uuid = IRUUID().CreateNew());
		void						DeleteObject(const IRUUID& uuid);

		InfinitRightObject*			GetObjectByUuid(const IRUUID& uuid);
	};

}