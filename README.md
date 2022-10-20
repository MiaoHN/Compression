# Compression

实现一些常见的文件压缩算法

## 实现算法

1. *Huffman*: 非常经典的变长压缩算法，详细内容见[这里](https://miaohn.github.io/huffman/)(完成了一部分)
2. *lzw*: 一个基于贪心的快速压缩算法，效果不错速度快(还在优化中)

## 测试文件

在 `scripts` 文件夹下有一个 [python 脚本](scripts/generate_data.py)，执行之：

```bash
python3 scripts/generate_data.py
```

即可下载一些可以用于测试的文件。当然还可以自己找

## License

[MIT](./LICENSE)

<!-- ## Reference -->

<!-- - [A New Approach of a Memory Efficient Huffman Tree Representation Technique](https://sci-hub.se/10.1109/ICIEV.2012.6317482) -->
