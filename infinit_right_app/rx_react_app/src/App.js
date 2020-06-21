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
      <Button onClick={(e) => {InfinitCore.IR_CreateNewObject({ObjectType: 0, Count: 3, Name: "Drawing Object"})}} >Create New Object</Button>
      <SceneTreeComponent />
    </Segment>
  }
}


export default App;
