/*
 * MP3File.hpp
 *
 *  Created on: 2 May 2018
 *      Author: julianporter
 */

#ifndef MP3FILE_HPP_
#define MP3FILE_HPP_

#include "base.hpp"
#include "ID3Header.hpp"
#include "PCMFile.hpp"

namespace pylame {

class MP3File {
private:
	id3::ID3Header parameters;
	cdata_t out;
	double duration;

public:
	MP3File(const unsigned quality,const unsigned rate) : parameters(quality,rate), out(), duration(0.0) {};
	MP3File(const id3::ID3Header &p) : parameters(p), out(), duration(0.0) {};
	virtual ~MP3File() = default;

	void transcode(pcm::PCMFile *pcm);
	void transcode(const pcm::file_t &pcm);
	cdata_t::const_iterator cbegin() const { return out.cbegin(); };
	cdata_t::const_iterator cend() const { return out.cend(); };
	double getDuration() const { return duration; };
	unsigned getRate() const { return parameters.Rate(); };
	unsigned size() const { return (unsigned)out.size(); };
	const unsigned char * bytes() const { return out.data(); };
	const char *chars() const { return reinterpret_cast<const char *>(out.data()); };

	void set(const id3::ID3Field &tag,const std::string &v) { parameters.set(tag,v); };

};

} /* namespace pylam */

std::ostream & operator<<(std::ostream &o,const pylame::MP3File &mp3);

#endif /* MP3FILE_HPP_ */
