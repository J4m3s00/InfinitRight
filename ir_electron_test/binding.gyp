
{
  "targets": [
    {
      "target_name": "binding",
      "include_dirs": [
        "<!(node -e \"require('nan')\")", 
          "../infinit_right/src/"
      ],
      "sources": [ "../infinit_right/../scrpts/../infinit_right/src/drawing/infinit_right_drawing.cpp",
"../infinit_right/../scrpts/../infinit_right/src/infinit_right_uuid.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_action.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_value_change.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_value_create.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_manager.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_value.cpp",
"../infinit_right/../scrpts/../infinit_right/src/undo/infinit_right_undo_value_delete.cpp",
"../infinit_right/../scrpts/../infinit_right/src/infinit_right_app.cpp",
"../infinit_right/../scrpts/../infinit_right/src/properties/infinit_right_json_converter.cpp",
"../infinit_right/../scrpts/../infinit_right/src/properties/infinit_right_property.cpp",
"../infinit_right/../scrpts/../infinit_right/src/object/infinit_right_object.cpp",
"../infinit_right/../scrpts/../infinit_right/src/glm/detail/glm.cpp",
"/src/module_main.cpp"
 ],
       "defines": [ "DS_MAC" ]
    }
  ]
}
