#pragma once

namespace IR {

	class InfinitRightApp
	{
	public:
		InfinitRightApp();
		~InfinitRightApp();
	private:
		InfinitRightDrawing*			fActiveDrawing;
		IRVector<InfinitRightDrawing*>	fLoadedDrawings;

		InfinitRightUndoManager			fUndoManager;

		IRMap<IRString, TBridgeFn>		fBridgeFns;
		IRVector<TObjectConstFn>		fObjectTypes;
		IRMap<IRString, u32>			fObjectTypeNameIdMap;
	public:
		void							Initialize();

		void							SetActiveDrawing(InfinitRightDrawing* drawing);
		InfinitRightDrawing*			GetActiveDrawing();


		InfinitRightUndoManager&		GetUndoManager();

		void RegisterBridgeFunction(const IRString& name, const TBridgeFn& fn);
		IRJson CallBridgeFunction(const IRString& name, const IRJson& input);

		void RegisterObject(const IRString& name, const TObjectConstFn& fn);
		u32 GetObjectIdFromTypeName(const IRString& objectTypeName);

		static InfinitRightObject* new_object(u32 type, const IRUUID& uuid = IRUUID().CreateNew());
		//GETTER FOR THE INIT FN
	public:

		static InfinitRightApp& gApp()
		{
			static InfinitRightApp    instance;
			return instance;
		}
	};

}