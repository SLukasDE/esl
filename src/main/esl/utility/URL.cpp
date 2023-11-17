#include <esl/utility/URL.h>

#include <memory>

namespace esl {
inline namespace v1_6 {
namespace utility {

URL::URL(std::string aURL)
: url(std::move(aURL))
{
	const char *str = url.c_str();

	size_t pos = 0;
	const size_t len = url.size();

	for(NextFragment nextFragment = NextFragment::SCHEME; nextFragment != NextFragment::EMPTY;) {
		switch(nextFragment) {
		case NextFragment::SCHEME:
			nextFragment = parseScheme(pos, str, len);
			break;
		case NextFragment::HOSTNAME:
			nextFragment = parseHostname(pos, str, len);
			break;
		case NextFragment::PORT:
			nextFragment = parsePort(pos, str, len);
			break;
		case NextFragment::PATH:
			nextFragment = parsePath(pos, str, len);
			break;
		case NextFragment::QUERY:
			nextFragment = parseQuery(pos, str, len);
			break;
		case NextFragment::TAG:
			nextFragment = parseTag(pos, str, len);
			break;
		default:
			nextFragment = NextFragment::EMPTY;
			break;
		}
	}
}

const std::string& URL::toString() const noexcept {
	return url;
}

const Protocol& URL::getScheme() const noexcept {
	return scheme;
}

const std::string& URL::getHostname() const noexcept {
	return hostname;
}

const std::string& URL::getPort() const noexcept {
	return port;
}

const std::string& URL::getPath() const noexcept {
	return path;
}

const std::string& URL::getQuery() const noexcept {
	return query;
}

const std::string& URL::getTag() const noexcept {
	return tag;
}

URL::NextFragment URL::parseScheme(size_t& pos, const char* str, const size_t len) {
	size_t scheme_pos = pos;

	// remove preceding spaces.
	for(;pos<len && str[pos]==' '; pos++) {
	}
	if (str[pos] == '/') {
		scheme = Protocol();
		++pos;
		return NextFragment::PATH;
	}

	for(;pos<len && str[pos] != ':'; pos++) {
	}
	if(pos > len) {
		return NextFragment::EMPTY;
	}

	std::string tmpScheme = std::string(&str[scheme_pos], pos - scheme_pos);

	if(len-pos < 3) {
		return NextFragment::EMPTY;
	}
	if(str[pos++] != ':') {
		return NextFragment::EMPTY;
	}
	if(str[pos++] != '/') {
		return NextFragment::EMPTY;
	}
	if(str[pos++] != '/') {
		return NextFragment::EMPTY;
	}

	scheme = Protocol(std::move(tmpScheme));
	return NextFragment::HOSTNAME;
}

URL::NextFragment URL::parseHostname(size_t& pos, const char* str, const size_t len) {
	size_t host_pos = pos;

	for(;pos<len && str[pos]!=':' && str[pos]!='/' && str[pos]!='?'; pos++) {
	}
	hostname = std::string(&str[host_pos], pos - host_pos);

	if (pos < len) {
		switch(str[pos]) {
		case '/':
			++pos;
			return NextFragment::PATH;
		case '?':
			++pos;
			return NextFragment::QUERY;
		case ':':
			++pos;
			return NextFragment::PORT;
		default:
			break;
		}
	}

	return NextFragment::EMPTY;
}

URL::NextFragment URL::parsePort(size_t& pos, const char* str, const size_t len) {
	size_t port_pos = pos;

	for(;pos<len && str[pos]!='/' && str[pos]!='?' ;pos++) {
	}
	port = std::string(&str[port_pos], pos - port_pos);

	if (pos < len) {
		switch(str[pos]) {
		case '/':
			++pos;
			return NextFragment::PATH;
		case '?':
			++pos;
			return NextFragment::QUERY;
		default:
			break;
		}
	}

	return NextFragment::EMPTY;
}

URL::NextFragment URL::parsePath(size_t& pos, const char* str, const size_t len) {
	size_t path_pos = pos;

	for(;pos<len && str[pos]!='?' && str[pos]!='#';pos++) {
	}
	path = std::string(&str[path_pos], pos - path_pos);

	if (pos < len) {
		switch(str[pos]) {
		case '?':
			++pos;
			return NextFragment::QUERY;
		case '#':
			++pos;
			return NextFragment::TAG;
		default:
			break;
		}
	}

	return NextFragment::EMPTY;
}

URL::NextFragment URL::parseQuery(size_t& pos, const char* str, const size_t len) {
	size_t param_pos = pos;

	for(;pos<len && str[pos]!='#';pos++) {
	}
	query = std::string(&str[param_pos], pos - param_pos);

	if (pos < len) {
		switch(str[pos]) {
		case '#':
			++pos;
			return NextFragment::TAG;
		default:
			break;
		}
	}

	return NextFragment::EMPTY;
}

URL::NextFragment URL::parseTag(size_t& pos, const char* str, const size_t len) {
	tag = std::string(&str[pos]);
	return NextFragment::EMPTY;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
