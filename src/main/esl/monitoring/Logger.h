/*
 * This file is part of ESL.
 * Copyright (C) 2020-2023 Sven Lukas
 *
 * ESL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ESL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with ESL.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ESL_MONITORING_LOGGER_H_
#define ESL_MONITORING_LOGGER_H_

#include <esl/monitoring/Streams.h>

#include <esa/monitoring/Logger.h>

namespace esl {
inline namespace v1_6 {
namespace monitoring {

template<Streams::Level level>
using Logger = esa::monitoring::Logger<level>;

} /* namespace monitoring */
} /* inline namespace v1_6 */
} /* namespace esl */

#define ESL__LOGGER_ERROR_OBJ(OBJ, ...) logger.write(logger.error, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_ERROR_THIS(...)     logger.write(logger.error, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_ERROR(...)          logger.write(logger.error, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_WARN_OBJ(OBJ, ...) logger.write(logger.warn, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_WARN_THIS(...)     logger.write(logger.warn, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_WARN(...)          logger.write(logger.warn, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_INFO_OBJ(OBJ, ...) logger.write(logger.info, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_INFO_THIS(...)     logger.write(logger.info, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_INFO(...)          logger.write(logger.info, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_DEBUG_OBJ(OBJ, ...) logger.write(logger.debug, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_DEBUG_THIS(...)     logger.write(logger.debug, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_DEBUG(...)          logger.write(logger.debug, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#define ESL__LOGGER_TRACE_OBJ(OBJ, ...) logger.write(logger.trace, OBJ, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_TRACE_THIS(...)     logger.write(logger.trace, this, __func__, __FILE__, __LINE__, __VA_ARGS__);
#define ESL__LOGGER_TRACE(...)          logger.write(logger.trace, nullptr, __func__, __FILE__, __LINE__, __VA_ARGS__);

#endif /* ESL_MONITORING_LOGGER_H_ */
