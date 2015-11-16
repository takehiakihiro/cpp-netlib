//          Copyright Dean Michael Berris 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NETWORK_MESSAGE_HPP__
#define BOOST_NETWORK_MESSAGE_HPP__

#include <boost/network/detail/directive_base.hpp>
#include <boost/network/detail/wrapper_base.hpp>
#include <boost/network/message/directives.hpp>
#include <boost/network/message/message_concept.hpp>
#include <boost/network/message/modifiers/add_header.hpp>
#include <boost/network/message/modifiers/body.hpp>
#include <boost/network/message/modifiers/clear_headers.hpp>
#include <boost/network/message/modifiers/destination.hpp>
#include <boost/network/message/modifiers/remove_header.hpp>
#include <boost/network/message/modifiers/source.hpp>
#include <boost/network/message/transformers.hpp>
#include <boost/network/message/wrappers.hpp>
#include <boost/network/message_fwd.hpp>
#include <boost/network/traits/string.hpp>
#include <boost/utility/enable_if.hpp>

/** message.hpp
 *
 * This header file implements the common message type which
 * all networking implementations under the boost::network
 * namespace. The common message type allows for easy message
 * construction and manipulation suited for networked
 * application development.
 */
namespace boost {
namespace network {

/** The common message type.
 */
template <class Tag>
struct basic_message {
 public:
  typedef Tag tag;

  typedef typename headers_container<Tag>::type headers_container_type;
  typedef typename headers_container_type::value_type header_type;
  typedef typename string<Tag>::type string_type;

  basic_message() = default;
  basic_message(const basic_message&) = default;
  basic_message(basic_message&&) noexcept = default;
  basic_message& operator=(basic_message const&) = default;
  basic_message& operator=(basic_message&&) = default;
  ~basic_message() = default;

  void swap(basic_message<Tag>& other) {
    using std::swap;
    swap(other.headers_, headers_);
    swap(other.body_, body_);
    swap(other.source_, source_);
    swap(other.destination_, destination_);
  }

  headers_container_type& headers() { return headers_; }

  void headers(headers_container_type headers) const {
    headers_ = std::move(headers);
  }

  void add_header(
      typename headers_container_type::value_type const& pair_) const {
    headers_.insert(pair_);
  }

  void remove_header(
      typename headers_container_type::key_type const& key) const {
    headers_.erase(key);
  }

  headers_container_type const& headers() const { return headers_; }

  string_type& body() { return body_; }

  void body(string_type body) const { body_ = std::move(body); }

  string_type const& body() const { return body_; }

  string_type& source() { return source_; }

  void source(string_type source) const { source_ = std::move(source); }

  string_type const& source() const { return source_; }

  string_type& destination() { return destination_; }

  void destination(string_type destination) const {
    destination_ = std::move(destination);
  }

  string_type const& destination() const { return destination_; }

 private:
  friend struct detail::directive_base<Tag>;
  friend struct detail::wrapper_base<Tag, basic_message<Tag> >;

  mutable headers_container_type headers_;
  mutable string_type body_;
  mutable string_type source_;
  mutable string_type destination_;
};

template <class Tag>
inline void swap(basic_message<Tag>& left, basic_message<Tag>& right) {
  // swap for ADL
  left.swap(right);
}

// Commenting this out as we don't need to do this anymore.
// BOOST_CONCEPT_ASSERT((Message<basic_message<boost::network::tags::default_string>
// >));
// BOOST_CONCEPT_ASSERT((Message<basic_message<boost::network::tags::default_wstring>
// >));
typedef basic_message<tags::default_string> message;
typedef basic_message<tags::default_wstring> wmessage;

}  // namespace network
}  // namespace boost

#endif  // BOOST_NETWORK_MESSAGE_HPP__
