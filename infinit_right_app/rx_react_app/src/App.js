import React from 'react';
import {Segment, Button, Form} from "semantic-ui-react"
import SceneTreeComponent from './components/SceneTreeComponent';
import InfinitCore from './server_connection';
import { OBJECT_TYPE_DrawingObject } from './callback';

class App extends React.Component
{
  componentDidMount()
  {
  }

  render()
  {
    return <Segment>
      <Form>
        <Form.Group>
          <Button onClick={(e) => {InfinitCore.IR_CreateNewObject({ObjectType: OBJECT_TYPE_DrawingObject, Count: 3, Name: "Drawing Object"})}} >Create New Object</Button>
          <Button onClick={(e) => {InfinitCore.IR_DoUndo()}} >Undo</Button>
          <Button onClick={(e) => {InfinitCore.IR_DoRedo()}} >Redo</Button>
        </Form.Group>

      </Form>
      <SceneTreeComponent />
    </Segment>
  }
}


export default App;
