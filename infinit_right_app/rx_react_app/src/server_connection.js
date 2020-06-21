import { RunCallback } from "./callback"

export let ServerConnection = {
    socket: null,
    cbfn: (args) => {},
    setupConnect: function () {
        // eslint-disable-next-line no-undef
        this.socket = io("http://localhost:420")
        this.socket.on("callback", (object) => {RunCallback(object)})
    },
    call: function (commandString, args) {
      return new Promise((resolve, reject) => {
          if(!this.socket) { reject(); } 
          this.socket.emit("corecall", {Command: commandString, Args: args}, (res) => {resolve(res)} )
      })
    }
}

class InfinitCore {}

InfinitCore.IR_CreateNewObject = async function (object)
{
    let result = await ServerConnection.call("IR_CreateNewObject", object)
    return result;
}

InfinitCore.IR_GetSceneTree = async function (object)
{
    let result = await ServerConnection.call("IR_GetSceneTree", object);
    return result;
}

export default InfinitCore;