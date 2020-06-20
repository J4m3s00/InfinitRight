import React from 'react';
import Infinit from './server_connection';

class App extends React.Component
{
  componentDidMount()
  {
  }

  render()
  {
    return <div>
      <button onClick={(e) => { Infinit.IR_CreateNewObject({}); } }></button>
    </div>
  }
}


export default App;
