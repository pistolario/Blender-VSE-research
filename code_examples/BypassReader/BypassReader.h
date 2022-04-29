/*******************************************************************************
* Copyright 2022 Marcos Pérez González
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

#pragma once

/**
* @file ConvolverReader.h
* @ingroup fx
* The ConvolverReader class.
*/

#include "IReader.h"
#include "ISound.h"
#include "sequence/ChangeableProperty.h"

#include <memory>
#include <vector>
#include <future>

AUD_NAMESPACE_BEGIN

/**
* This class represents a reader for a sound that can be modified depending on a given impulse response.
*/
class AUD_API BypassReader : public IReader
{
private:

	/**
	* The reader of the input sound.
	*/
	std::shared_ptr<IReader> m_reader;

	// Internal Reader, posible to change
	std::shared_ptr<IReader> internalReader;

	std::shared_ptr<ChangeableProperty> prop;

	// delete copy constructor and operator=
	BypassReader(const BypassReader&) = delete;
	BypassReader& operator=(const BypassReader&) = delete;

public:
	/**
	* Creates a new convolver reader.
	* \param reader A reader of the input sound to be assigned this bypass reader.
	*/
	BypassReader(std::shared_ptr<IReader> reader);
	virtual ~BypassReader();

	virtual bool isSeekable() const;
	virtual void seek(int position);
	virtual int getLength() const;
	virtual int getPosition() const;
	virtual Specs getSpecs() const;
	virtual void read(int& length, bool& eos, sample_t* buffer);
	virtual void setProperty(std::shared_ptr<ChangeableProperty> property);
	void changeInternalReader(std::shared_ptr<IReader> reader);
	std::shared_ptr<IReader> getInternalReader();
	std::shared_ptr<IReader> getPreviousReader();
};

AUD_NAMESPACE_END
