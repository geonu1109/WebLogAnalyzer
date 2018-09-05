#include "DataInput.h"

DataInput::DataInput()
{
}

DataInput::~DataInput()
{
}

void DataInput::setDate(const string &strDate) {
	m_nYear = stoi(strDate.substr(0, 4));
	m_nMonth = stoi(strDate.substr(4, 2));
	m_nDay = stoi(strDate.substr(6, 2));
}

void DataInput::setTimeStart(const string &strTime) {
	m_nHourStart = stoi(strTime.substr(0, 2));
	m_nMinuteStart = stoi(strTime.substr(2, 2));
	m_nSecondStart = stoi(strTime.substr(4, 2));
}
void DataInput::setTimeEnd(const string &strTime) {
	m_nHourEnd = stoi(strTime.substr(0, 2));
	m_nMinuteEnd = stoi(strTime.substr(2, 2));
	m_nSecondEnd = stoi(strTime.substr(4, 2));
}

void DataInput::setDelayLimit(const int &nDelayLimit) {
	m_nDelayLimit = nDelayLimit;
}

const int DataInput::getYear(void) const {
	return m_nYear;
}

const int DataInput::getMonth(void) const {
	return m_nMonth;
}

const int DataInput::getDay(void) const {
	return m_nDay;
}

const int DataInput::getHourStart(void) const {
	return m_nHourStart;
}

const int DataInput::getMinuteStart(void) const {
	return m_nMinuteStart;
}

const int DataInput::getSecondStart(void) const {
	return m_nSecondStart;
}

const int DataInput::getHourEnd(void) const {
	return m_nHourEnd;
}

const int DataInput::getMinuteEnd(void) const {
	return m_nMinuteEnd;
}

const int DataInput::getSecondEnd(void) const {
	return m_nSecondEnd;
}

const int DataInput::getDelayLimit(void) const {
	return m_nDelayLimit;
}