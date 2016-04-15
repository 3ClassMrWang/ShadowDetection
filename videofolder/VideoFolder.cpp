
#include "VideoFolder.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

const string toPath(const string& path, const char sep) {
	const char lastChar = *(--path.end());
	if (lastChar != sep) {
		return path + sep;
	}
	return path;
}

bool fileExists(const string& path) {
	ifstream f(path.c_str());
	return f.is_open();
}

VideoFolder::VideoFolder(const string& videoPath, const string& binaryPath)
	: sep((videoPath.find('\\') != string::npos) ? '\\' : '/'),
	binaryExtension(binaryPath),
	videoPath(toPath(videoPath, sep)),
	binaryPath(toPath(binaryPath, sep))
{}

void VideoFolder::readTemporalFile() {
	const string filePath = videoPath + "temporalROI.txt";
	ifstream f(filePath.c_str());
	if (f.is_open()) {
		if (f.good()) {
			string line;
			getline(f, line);

			uint from, to;
			istringstream iss(line);
			iss >> from >> to;

			range = make_pair(from, to);
		}
		f.close();
	} else {
		throw string("Unable to open the file : ") + videoPath + "temporalROI.txt";
	}
}

void VideoFolder::setExtension() {
	string extensions[] = {".png", ".jpg", ".jpeg", ".bmp", ".ppm"};
	vector<string> exts(extensions, extensions + 5);

	const string firstBinaryFrame = binaryFrame(range.first);

	for (auto it = exts.begin(); it < exts.end(); ++it) {
		const string &ext = *it;
		if (fileExists(binaryPath + "bin" + toFrameNumber(range.first) + ext)) {
			binaryExtension = ext;
			return;
		}
	}
	throw string("You must use png or jp[e]g extension.");
}

const string VideoFolder::firstFrame() const {
	return inputFrame(1);
}

const string VideoFolder::inputFrame(const uint idx) const {
	return videoPath + "input/in" + toFrameNumber(idx) + ".jpg";
}

const string VideoFolder::binaryFrame(const uint idx) const {
	return binaryPath + "bin" + toFrameNumber(idx) + ".jpg";
}

const string VideoFolder::gtFrame(const uint idx) const {
	return videoPath + "groundtruth/gt" + toFrameNumber(idx) + ".png";
}

//添加背景模型图片
const string VideoFolder::bgmodelFrame(const uint idx) const {
	return binaryPath + "bg" + toFrameNumber(idx) + ".jpg";
}
//添加算法运行时间存储文件的路径
const string VideoFolder::runTimeFile() const {
	return binaryPath + "runTimeFile.txt";
}

const string VideoFolder::toFrameNumber(const uint idx) const {
	ostringstream oss;
	oss << setfill('0') << setw(6) << idx;
	return oss.str();
}
