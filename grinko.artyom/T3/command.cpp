#include "command.h"

#include <cassert>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <functional>

#include "streamGuard.h"
#include "geometry.h"
#include "areaAndCount.h"
#include "minAndMax.h"

Command::Result Command::operator()(const Polygons &polygons) const {
    return this->command(polygons);
}

std::istream &operator>>(std::istream &stream, Command &command) {
    using namespace std::placeholders;

    std::istream::sentry sentry{stream};
    if (sentry) {
        std::string input{};
        stream >> input;
        if (!stream) {
            return stream;
        }

        if (input == "AREA") {
            std::string subcommand{};
            stream >> subcommand;
            if (!stream) {
                return stream;
            }

            if (subcommand == "EVEN") {
                command.command = area<AreaAndCount::Type::Even>;
            } else if (subcommand == "ODD") {
                command.command = area<AreaAndCount::Type::Odd>;
            } else if (subcommand == "MEAN") {
                command.command = area<AreaAndCount::Type::Mean>;
            } else {
                size_t numberOfVertices = 0;
                if (!(std::stringstream{subcommand} >> numberOfVertices) ||
                    numberOfVertices < 3) {
                    stream.setstate(std::ios::failbit);

                    return stream;
                }

                command.command = std::bind(area<AreaAndCount::Type::NumberOfVertices>,
                                            numberOfVertices,
                                            _1);
            }
        } else if (input == "MAX") {
            std::string subcommand{};
            stream >> subcommand;
            if (!stream) {
                return stream;
            }

            if (subcommand == "AREA") {
                command.command = max<MinAndMax::Type::Area>;
            } else if (subcommand == "VERTEXES") {
                command.command = max<MinAndMax::Type::Vertices>;
            } else {
                stream.setstate(std::ios::failbit);
            }
        } else if (input == "MIN") {
            std::string subcommand{};
            stream >> subcommand;
            if (!stream) {
                return stream;
            }

            if (subcommand == "AREA") {
                command.command = min<MinAndMax::Type::Area>;
            } else if (subcommand == "VERTEXES") {
                command.command = min<MinAndMax::Type::Vertices>;
            } else {
                stream.setstate(std::ios::failbit);
            }
        } else if (input == "COUNT") {
            std::string subcommand{};
            stream >> subcommand;
            if (!stream) {
                return stream;
            }

            if (subcommand == "EVEN") {
                command.command = count<AreaAndCount::Type::Even>;
            } else if (subcommand == "ODD") {
                command.command = count<AreaAndCount::Type::Odd>;
            } else {
                size_t numberOfVertices = 0;
                if (!(std::stringstream{subcommand} >> numberOfVertices) ||
                    numberOfVertices < 3) {
                    stream.setstate(std::ios::failbit);

                    return stream;
                }

                command.command = std::bind(count<AreaAndCount::Type::NumberOfVertices>,
                                            numberOfVertices,
                                            _1);
            }
        } else {
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Command::Result &result) {
    std::ostream::sentry sentry{stream};
    if (sentry) {
        switch (result.type) {
        case Command::Result::Type::Real: {
            StreamGuard streamGuard{stream};
            stream << std::fixed <<
                      std::setprecision(1) <<
                      result.value.real;
        } break;

        case Command::Result::Type::Size:
            stream << result.value.size;

            break;

        case Command::Result::Type::InvalidCommand:
            stream << "<INVALID COMMAND>";

            break;

        default:
            assert(false && "You're not supposed to get here.");

            break;
        }
    }

    return stream;
}
