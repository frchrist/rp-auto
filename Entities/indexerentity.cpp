#include "indexerentity.h"

IndexerEntity::IndexerEntity() {}

IndexerEntity::IndexerEntity(int id, STATE state, WHY reason) : _id(id), _state(state), _reason(reason)
{}

IndexerEntity::STATE IndexerEntity::getState() const
{
    return _state;
}

void IndexerEntity::setState(IndexerEntity::STATE newState)
{
    _state = newState;
}

IndexerEntity::WHY IndexerEntity::getReason() const
{
    return _reason;
}

void IndexerEntity::setReason(IndexerEntity::WHY newReason)
{
    _reason = newReason;
}

int IndexerEntity::id() const
{
    return _id;
}

void IndexerEntity::setId(int newId)
{
    _id = newId;
}
