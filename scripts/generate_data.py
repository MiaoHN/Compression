#!/bin/env python3

# Download test files
# extracted files will be located to current working directory

import tarfile
import requests
import os


if __name__ == '__main__':
    url = 'http://corpus.canterbury.ac.nz/resources/calgary.tar.gz'
    output_dir = 'datas'
    temp_file = 'test_data.tar.gz'
    if os.path.exists(output_dir):
        exit()

    r = requests.get(url)
    with open(temp_file, 'wb') as f:
        f.write(r.content)

    tar_file = tarfile.open(temp_file, 'r')
    tar_file.extractall(path=output_dir)
    os.remove(temp_file)
