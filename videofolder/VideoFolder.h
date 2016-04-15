	
#pragma once

#include <string>

#include "types.h"

typedef pair<uint, uint> imgRange;

class VideoFolder
{
	public:
		VideoFolder(const string& videoPath, const string& binaryPath);

		void readTemporalFile();
		void setExtension();

		const string firstFrame() const;
		const string inputFrame(const uint idx) const;
		const string binaryFrame(const uint idx) const;
		const string gtFrame(const uint idx) const;
		//添加背景保存文件
		const string bgmodelFrame(const uint idx) const;
		//添加保存算法运行时间文件路径
		const string runTimeFile() const;

		const imgRange getRange() const { return range; }
		const string getVideoPath() const { return videoPath; }

	private:
		const char sep;
		string binaryExtension;

		const string videoPath;
		const string binaryPath;
		imgRange range;

		const string toFrameNumber(const uint idx) const;
};

