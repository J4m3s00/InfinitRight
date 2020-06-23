import React from "react"
import { Segment, Card } from "semantic-ui-react";
import { RegisterCallbackFn, CHANGE_TYPE_Create, OBJECT_TYPE_DrawingObject, CHANGE_TYPE_Delete, CHANGE_TYPE_Change } from "../callback";
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
        RegisterCallbackFn(CHANGE_TYPE_Change, OBJECT_TYPE_DrawingObject, (changeList) => {
            console.log("Dtrawing object change: ", changeList)
            changeList.forEach(changeObj => {
                let object = this.getObjectByUuid(changeObj.UUID);
                if (object)
                {
                    Object.entries(changeObj.NewValue).forEach(([key, value]) => {
                        object[key] = value;
                    });
                }
            })
            this.setState({objects: this.state.objects})
        })

        this.rebuildSceneTree();
    }

    render()
    {
        return <Segment>
            <Card.Group itemsPerRow="4">
                {this.state.objects.map(obj => {
                    return <Card key={obj.UUID} link fluid color={obj.Selected ? "grey" : ""} onClick={(e) => { InfinitCore.IR_SetObject({UUID: obj.UUID, Selected: !obj.Selected}) }}><Card.Content>
                    <Card.Header></Card.Header>
                    {obj.Name}
                    <Card.Meta></Card.Meta>
                </Card.Content></Card>
                })}
            </Card.Group>
        </Segment>
    }

    rebuildSceneTree = async () =>
    {
        let coreResult = await InfinitCore.IR_GetSceneTree();
        this.setState({objects: coreResult.Objects})
    }

    getObjectByUuid(uuid)
    {
        for (let i = 0; i < this.state.objects.length; i++)
        {
            if (this.state.objects[i].UUID === uuid)
            {
                return this.state.objects[i];
            }
        }
        return undefined;
    }
}

export default SceneTreeComponent;