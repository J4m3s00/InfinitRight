cmake_minimum_required(VERSION 3.15)

FIND_LIBRARY(COCOA_LIBRARY Cocoa)
SET(EXTRA_LIBS ${COCOA_LIBRARY})

add_library(InfinitRight            src/infinit_right_app.cpp
                                    src/infinit_right_uuid.cpp
                                    src/drawing/infinit_right_drawing.cpp
                                    src/object/infinit_right_object.cpp
                                    src/properties/infinit_right_property.cpp
                                    src/properties/infinit_right_json_converter.cpp
                                    src/undo/infinit_right_undo_action.cpp
                                    src/undo/infinit_right_undo_manager.cpp
                                    src/undo/infinit_right_undo_value.cpp
                                    src/undo/infinit_right_undo_value_change.cpp
                                    src/undo/infinit_right_undo_value_create.cpp
                                    src/undo/infinit_right_undo_value_delete.cpp
                                    )

target_link_libraries(InfinitRight ${EXTRA_LIBS})