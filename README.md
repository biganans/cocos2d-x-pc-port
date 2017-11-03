# cocos2d-x-pc-port
All features is implement on cocos2d-x latest version, since v3.13
# use
include crypto_wrapper.h

用法: 包含crypto_wrapper.h即可

// 复用内存方式:
std::string msg1 = "hello world, ok!";
crypto::aes::overlapped::encrypt(msg1);
crypto::aes::overlapped::decrypt(msg2);
// 普通方式
std::string ciphertext = crypto::aes::encrypt(msg1);
std::string plaintext = crypto::aes::decrypt(ciphertext);
