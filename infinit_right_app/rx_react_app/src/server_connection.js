
export let ServerConnection = {
    socket: null,
    setupConnect: function () {
        // eslint-disable-next-line no-undef
        this.socket = io("http://localhost:420")
    },
    call: function (commandString, args) {
      return new Promise((resolve, reject) => {
          if(!this.socket) { reject(); } 
          this.socket.emit("corecall", {Command: commandString, Args: args}, resolve)
      })
    }
}

let Infinit = {}

Infinit.IR_CreateNewObject = async function (object)
{
    let result = await ServerConnection.call("IR_CreateNewObject", object)
    return result;
}

export default Infinit;