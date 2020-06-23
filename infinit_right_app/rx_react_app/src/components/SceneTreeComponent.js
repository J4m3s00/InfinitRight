import React from "react"
import { Segment, List, Card } from "semantic-ui-react";
import { RegisterCallbackFn, CHANGE_TYPE_Create, OBJECT_TYPE_DrawingObject, CHANGE_TYPE_Delete } from "../callback";
import InfinitCore from "../server_connection";

class SceneTreeComponent extends React.Component
{
    constructor(props)
    {
        super(props)

        this.state = {
            objects: []
        }
    }

    componentDidMount()
    {
        RegisterCallbackFn(CHANGE_TYPE_Create, OBJECT_TYPE_DrawingObject, () => {
            this.rebuildSceneTree();
        })
        RegisterCallbackFn(CHANGE_TYPE_Delete, OBJECT_TYPE_DrawingObject, () => {
            this.rebuildSceneTree();
        })

        this.rebuildSceneTree();
    }

    render()
    {
        return <Segment>
            {this.state.objects.map(obj => {
                return <Card>{obj.Name}</Card>
            })}
        </Segment>
    }

    rebuildSceneTree = async () =>
    {
        let coreResult = await InfinitCore.IR_GetSceneTree();
        this.setState({objects: coreResult.Objects})
    }
}

export default SceneTreeComponent;