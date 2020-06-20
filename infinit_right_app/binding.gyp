{
  "targets": [
    {
      "target_name": "InfinitRight",
      "include_dirs": [
            "<!(node -e \"require('nan')\")", 

          "../infinit_right/src/"
      ],
      "sources": [  "../infinit_right/src/drawing/infinit_right_drawing.cpp",
                    "../infinit_right/src/infinit_right_uuid.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_action.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_value_change.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_value_create.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_manager.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_value.cpp",
                    "../infinit_right/src/undo/infinit_right_undo_value_delete.cpp",
                    "../infinit_right/src/infinit_right_app.cpp",
                    "../infinit_right/src/properties/infinit_right_json_converter.cpp",
                    "../infinit_right/src/properties/infinit_right_property.cpp",
                    "../infinit_right/src/object/infinit_right_object.cpp",
                    "core/objects/infinit_right_drawing_object.cpp",
                    "core/module_main.cpp"
 ],
       "defines": [ "IR_MAC", "IR_NAN_SUPPORT" ]
    }
  ]
}