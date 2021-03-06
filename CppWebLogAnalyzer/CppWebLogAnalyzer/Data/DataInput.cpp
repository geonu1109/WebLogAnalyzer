#include "DataInput.h"
#include <iostream>

DataInput DataInput::instance;

DataInput::DataInput()
{
}

DataInput::~DataInput()
{
}

void DataInput::setSelect(const int &nSelect) {
	m_nSelect = nSelect;
}

void DataInput::setDate(const string &strDate) {
	m_tmDate.tm_year = stoi(strDate.substr(0, 4));
	m_tmDate.tm_mon = stoi(strDate.substr(4, 2));
	m_tmDate.tm_mday = stoi(strDate.substr(6, 2));
}

void DataInput::setTimeStart(const string &strTime) {
	m_tmTimeStart.tm_hour = stoi(strTime.substr(0, 2));
	m_tmTimeStart.tm_min = stoi(strTime.substr(2, 2));
	m_tmTimeStart.tm_sec = stoi(strTime.substr(4, 2));
}
void DataInput::setTimeEnd(const string &strTime) {
	m_tmTimeEnd.tm_hour = stoi(strTime.substr(0, 2));
	m_tmTimeEnd.tm_min = stoi(strTime.substr(2, 2));
	m_tmTimeEnd.tm_sec = stoi(strTime.substr(4, 2));
}

void DataInput::setDelayLimit(const int &nDelayLimit) {
	m_nDelayLimit = nDelayLimit;
}

void DataInput::setHttpStatusCode(const int &nHttpStatusCode) {
	m_nHttpStatusCode = nHttpStatusCode;
}

void DataInput::setHttpRequestMethod(const string &strHttpRequestMethod) {
	m_strHttpRequestMethod = strHttpRequestMethod;
}

const int DataInput::getSelect(void) {
	return m_nSelect;
}

const tm DataInput::getDate(void) {
	return m_tmDate;
}

const tm DataInput::getTimeStart(void) {
	return m_tmTimeStart;
}

const tm DataInput::getTimeEnd(void) {
	return m_tmTimeEnd;
}

const int DataInput::getDelayLimit(void) {
	return m_nDelayLimit;
}

const int DataInput::getHttpStatusCode(void) {
	return m_nHttpStatusCode;
}

const string DataInput::getHttpRequestMethod(void) {
	return m_strHttpRequestMethod;
}

DataInput &DataInput::getInstance(void) {
	return instance;
}