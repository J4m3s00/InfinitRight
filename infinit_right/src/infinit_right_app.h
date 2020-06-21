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
		IRMap<IRString, IRObjectId>		fObjectTypeNameIdMap;
		TCallbackFn						fRegisteredCallbackFunction;

		void*							fUserData;
	public:
		void							Initialize();

		void							SetActiveDrawing(InfinitRightDrawing* drawing);
		InfinitRightDrawing*			GetActiveDrawing();


		InfinitRightUndoManager&		GetUndoManager();

		void RegisterChangeCallbackFunction(const TCallbackFn& fn);
		void StartChangeCallback(const IRJson& args);

		void RegisterBridgeFunction(const IRString& name, const TBridgeFn& fn);
		IRJson CallBridgeFunction(const IRString& name, const IRJson& input);

		void RegisterObject(const IRString& name, const TObjectConstFn& fn);
		IRObjectId GetObjectIdFromTypeName(const IRString& objectTypeName);

		static InfinitRightObject* new_object(u32 type, const IRUUID& uuid = IRUUID().CreateNew());


		template <typename T>
		T* UserData() 
		{
			return (T*) fUserData;
		}

		template <typename T>
		void SetUserData(T* data)
		{
			fUserData = (void*) data;
		}

		//GETTER FOR THE INIT FN
	public:

		static InfinitRightApp& gApp()
		{
			static InfinitRightApp    instance;
			return instance;
		}
	};

}