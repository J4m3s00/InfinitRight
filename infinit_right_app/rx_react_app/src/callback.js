
export const CHANGE_TYPE_Change = "change";
export const CHANGE_TYPE_Create = "create";
export const CHANGE_TYPE_Delete = "delete";


export const OBJECT_TYPE_DrawingObject = 1;


let RegisteredCallbacks = {
    [CHANGE_TYPE_Change]: {},
    [CHANGE_TYPE_Create]: {},
    [CHANGE_TYPE_Delete]: {},
}

export let globalCallbacks = {};

export function RegisterCallbackFn(changeType, objectId, cbfn)
{
    if (!RegisteredCallbacks[changeType][objectId]) { RegisteredCallbacks[changeType][objectId] = []}
    RegisteredCallbacks[changeType][objectId].push(cbfn);
}

export function RunCallback(object)
{
    console.log("Run callback: ", RegisteredCallbacks);
    if (object[CHANGE_TYPE_Create])
    {
        Object.entries(object[CHANGE_TYPE_Create]).forEach(([key, value]) => {
            console.log("create-object-type-", key);
            if (Array.isArray(RegisteredCallbacks[CHANGE_TYPE_Create][key]))
            {
                RegisteredCallbacks[CHANGE_TYPE_Create][key].forEach(cbfn => cbfn(value));
            }
        })
    }
    if (object[CHANGE_TYPE_Delete])
    {
        Object.entries(object[CHANGE_TYPE_Delete]).forEach(([key, value]) => {
            console.log("delete-object-type-", key);
            if (RegisteredCallbacks[CHANGE_TYPE_Delete][key])
            {
                RegisteredCallbacks[CHANGE_TYPE_Delete][key].forEach(cbfn => cbfn(value));
            }
        })
    }
    if (object[CHANGE_TYPE_Change])
    {
        Object.entries(object[CHANGE_TYPE_Change]).forEach(([key, value]) => {
            console.log("change-object-type-", key);
            if (RegisteredCallbacks[CHANGE_TYPE_Change][key])
            {
                RegisteredCallbacks[CHANGE_TYPE_Change][key].forEach(cbfn => cbfn(value));
            }
        })
    }
}