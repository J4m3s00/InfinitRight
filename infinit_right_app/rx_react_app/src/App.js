import React from 'react';
import {Segment, Button} from "semantic-ui-react"
import SceneTreeComponent from './components/SceneTreeComponent';
import InfinitCore from './server_connection';

class App extends React.Component
{
  componentDidMount()
  {
  }

  render()
  {
    return <Segment>
      <Button onClick={(e) => {InfinitCore.IR_CreateNewObject({})}} >Create New Object</Button>
      <SceneTreeComponent />
    </Segment>
  }
}


export default App;
