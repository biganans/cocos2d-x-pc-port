# cocos2d-x-pc-port
* Full resource encrypt/decrypt solution, you can choose any overlapped(no unnecessary memory copy) encrypt/decrypt algorithm, such as AES
* More commonly getFileData API: std::string FileUtils::getFileData(const std::string& filename), the return buffer, you can call std::move(fileData) at any where what you want to avoid unnecessary memory alloc & copy.
* Builtin ETC1 alpha channel supports. separated texture, alpha channel default File Name: xxx.pngAlpha
* Only contains different source code with latest cocos2d-x release for MFC.
cocos2d-x latest download: http://www.cocos2d-x.org/download

* 全量资源加密支持，可以使用任意可重叠复用内存的加密算法，例如AES高级加密算法
* 更加通用的文件数据读取接口，可一在任何地方调, 以标准库std::string作为返回值, 用std::move(fileData)来避免不必要的内存分配和拷贝
* 内建ETC1透明通道支持, 使用分离存储Alpha通道方式，默认Alpha通道存储文件名: xxx.pngAlpha
