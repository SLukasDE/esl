/*
MIT License
Copyright (c) 2019-2023 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESL_CRYPTO_PRIVATEKEY_H_
#define ESL_CRYPTO_PRIVATEKEY_H_

namespace esl {
inline namespace v1_6 {
namespace crypto {

#include <esl/crypto/PublicKey.h>
#include <esl/object/Object.h>
//#include <esl/plugin/Plugin.h>

#include <memory>
#include <string>

class PrivateKey : public object::Object {
public:
	//using Plugin = plugin::Plugin<PrivateKey>;

	virtual std::string getX509_DER(const std::string& password) const = 0;
	virtual std::string getX509_PEM(const std::string& password) const = 0;

	virtual std::unique_ptr<PublicKey> createPublicKey() const = 0;

	virtual std::string getAlgorithmName() const = 0;
	virtual unsigned int getAlgorithmBits() const = 0;

	virtual std::string decrypt(const std::string& ciphertextStr) const = 0;
	virtual std::string sign(const std::string& data, const std::string& algorithm = "RS512") const = 0;
};

} /* namespace crypto */
} /* inline namespace v1_6 */
} /* namespace esl */

#endif /* ESL_CRYPTO_PRIVATEKEY_H_ */
