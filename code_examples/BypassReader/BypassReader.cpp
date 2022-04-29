/*******************************************************************************
* Copyright 2015-2016 Juan Francisco Crespo Galán
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#include "fx/BypassReader.h"
#include "Exception.h"

#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>

AUD_NAMESPACE_BEGIN

BypassReader::BypassReader(std::shared_ptr<IReader> reader):
	m_reader(reader)
{
	prop = nullptr;
}


BypassReader::~BypassReader()
{
}

bool BypassReader::isSeekable() const
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		return internalReader->isSeekable();
	else
		return m_reader->isSeekable();
}

void BypassReader::seek(int position)
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		internalReader->seek(position);
	else
		m_reader->seek(position);
}

int BypassReader::getLength() const
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		return internalReader->getLength();
	else
		return m_reader->getLength();
}

int BypassReader::getPosition() const
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		return internalReader->getPosition();
	else
		return m_reader->getPosition();
}

Specs BypassReader::getSpecs() const
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		return internalReader->getSpecs();
	else
		return m_reader->getSpecs();
}

void BypassReader::read(int& length, bool& eos, sample_t* buffer)
{
	if(prop!=nullptr && prop->isDirty())
		prop->changeWhatever();
	if(internalReader!=nullptr)
		internalReader->read(length, eos, buffer);
	else
		m_reader->read(length, eos, buffer);
}

void BypassReader::changeInternalReader(std::shared_ptr<IReader> reader)
{
	int old_position = -1;
	if(internalReader!=nullptr)
		old_position=internalReader->getPosition();
	else
		old_position=m_reader->getPosition();

	internalReader = reader;
	if(internalReader!=nullptr)
		internalReader->seek(old_position);
}

void BypassReader::setProperty(std::shared_ptr<ChangeableProperty> property)
{
	prop = property;
}

std::shared_ptr<IReader> BypassReader::getInternalReader()
{
	return internalReader;
}

std::shared_ptr<IReader> BypassReader::getPreviousReader()
{
	return m_reader;
}

AUD_NAMESPACE_END
