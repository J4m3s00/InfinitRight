
export let ServerConnection = {
    socket: null,
    cbfn: (args) => {},
    setupConnect: function () {
        // eslint-disable-next-line no-undef
        this.socket = io("http://localhost:420")
        this.socket.on("callback", console.log)
    },
    call: function (commandString, args) {
      return new Promise((resolve, reject) => {
          if(!this.socket) { reject(); } 
          this.socket.emit("corecall", {Command: commandString, Args: args}, resolve)
      })
    }
}

class InfinitCore {}

InfinitCore.IR_CreateNewObject = async function (object)
{
    let result = await ServerConnection.call("IR_CreateNewObject", object)
    return result;
}

export default InfinitCore;