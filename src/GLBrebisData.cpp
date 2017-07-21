#include "GLBrebisData.h"

#include "Poco/Logger.h"
#include <algorithm>

std::vector<GLBrebisData::Enum> GLBrebisData::getAllUniqueDefines() const
{
    Poco::Logger &logger = Poco::Logger::get("GLBrebisData");
    std::vector<Enum> results;

    for(size_t i = 0; i < registry.enums.size(); ++i)
    {
        const Enums &parent = registry.enums[i];
        for(size_t j = 0; j < parent.entries.size(); ++j)
        {
            const Enum &candidate = registry.enums[i].entries[j];

            size_t k;
            for (k = 0; k < results.size(); ++k)
            {
                if (candidate.name == results[k].name)
                {
                    if (results[k].alias.length() > 0)
                    {
                        results[k] = candidate; // override if the one we had has an alias.
                    }
                    else if (candidate.alias.length() > 0)
                    {

                    }
                    else if (candidate.value != results[k].value)
                    {
                        logger.error("ALERT! Found duplicated definitions '%s' with different values: %s vs %s", candidate.name, candidate.value, results[k].value);
                    }
                    else
                    {
                        logger.warning("WARNING! Found duplicated definitions '%s' ", candidate.name);
                    }
                    break;
                }
            }

            if (k == results.size())
            {
                results.push_back(candidate);
            }
        }
    }

    std::sort(results.begin(), results.end());

    return results;
}

std::vector<GLBrebisData::Type> GLBrebisData::getAllUniqueTypes() const
{
    std::vector<Type> results;

    for(size_t i = 0; i < registry.types.size(); ++i) {
        const Type &candidate = registry.types[i];
        size_t k;
        for (k = 0; k < results.size(); ++k) {
            if (candidate.name == results[k].name) {
                results[k] = candidate; // override
                break;
            }
        }

        if (k == results.size()) {
            results.push_back(candidate);
        }
    }

    return results;
}

std::vector<GLBrebisData::Command> GLBrebisData::getAllUniqueFeatureCommands() const
{
    std::vector<Command> results;

    for(size_t i = 0; i < registry.features.size(); ++i)
    {
        const GLBrebisData::Feature &feature = registry.features[i];
        for(size_t j = 0; j < feature.commands.size(); ++j)
        {
            const std::string &commandName = feature.commands[j];

            for(size_t k = 0; k < registry.commands.size(); ++k)
            {
                const GLBrebisData::Command &commandB = registry.commands[k];
                if (commandName == commandB.proto.name)
                {
                    results.push_back(commandB);
                    break;
                }
            }
        }
    }

    std::sort(results.begin(), results.end());

    return results;
}

std::vector<GLBrebisData::Command> GLBrebisData::getAllUniqueExtensionCommands() const
{
    std::vector<Command> results;

    for(size_t i = 0; i < registry.extensions.size(); ++i)
    {
        const GLBrebisData::Extension &extension = registry.extensions[i];
        for(size_t j = 0; j < extension.commands.size(); ++j)
        {
            const std::string &commandName = extension.commands[j];

            for(size_t k = 0; k < registry.commands.size(); ++k)
            {
                const GLBrebisData::Command &commandB = registry.commands[k];
                if (commandName == commandB.proto.name)
                {
                    results.push_back(commandB);
                    break;
                }
            }
        }
    }

    std::sort(results.begin(), results.end());

    return results;
}

