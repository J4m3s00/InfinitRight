import os 
import sys

hey = "helo"

coreFileStr = "asd"

def appendFolderFile(path):
    result = ""
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            [_, file_extension] = os.path.splitext(file);
            if file_extension == ".cpp":
                result += "\"../infinit_right/" + os.path.join(path, file) + "\"" + ",\n"
        elif os.path.isdir(os.path.join(path, file)):
            result += appendFolderFile(path + file + "/")
    return result


coreFileStr = appendFolderFile(os.path.dirname(__file__) + "/../infinit_right/src/")
print (coreFileStr)


result = """
{
  "targets": [
    {
      "target_name": "binding",
      "include_dirs": [
          "../infinit_right/src/"
      ],
      "sources": [ """ + coreFileStr + """ ],
       "defines": [ "DS_MAC" ]
    }
  ]
}
"""

fd = os.open( sys.argv[1] + "/binding.gyp", os.O_RDWR)

l = str.encode(result)

os.write(fd, l)
os.close(fd)