// Fill out your copyright notice in the Description page of Project Settings.



#include "Group.h"

Group::Group()
{
}

Group::~Group()
{
}

void Group::AddChild(Behavior* _child)
{
  m_oChildren.Add(_child);
}
