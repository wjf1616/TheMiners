import os
def write_all_file(path):
    if os.path.isdir(path):
        for item in os.listdir(path):
            itemsrc = os.path.join(path, item)
            print(itemsrc)
            os.remove(itemsrc)

if __name__ == "__main__":
    dirname = os.getcwd()
    file_object = open(os.path.basename(dirname) + ".mk", 'w')
    file_object.write('SOURCE := ')
    dirlist = os.listdir(dirname)
    for item in dirlist:
        ext=os.path.splitext(item)[1]
        if (ext == '.cpp') and (item.find("win32") == -1) and (item.find("ios") == -1):
            file_object.write(' \\\n');
            file_object.write(item)
    file_object.close()
