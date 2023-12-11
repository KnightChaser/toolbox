import os

extensionToGrab = ".c"
outputFileName = "extracted.txt"

def find_c_files(directory):
    c_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(extensionToGrab):
                c_files.append(os.path.join(root, file))
    return c_files

def write_to_output(file_list):
    with open(outputFileName, 'w') as output_file:
        for file_path in file_list:
            try:
                print(f"Extracting... {file_path}")
                output_file.write(f"[ {file_path} ]\n\n")
                with open(file_path, 'r') as input_file:
                    output_file.write(input_file.read())
                    output_file.write("\n\n========================\n\n") 
            except:
                print(f"{file_path} got an exception while reading. pass.")
                pass

if __name__ == "__main__":
    current_directory = os.getcwd()
    c_files = find_c_files(current_directory)

    if len(c_files) > 0:
        write_to_output(c_files)
        print("File contents have been written to output.txt")
    else:
        print("No C files found in the current directory and its subdirectories.")
