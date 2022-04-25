#pragma once

class MObject 
{

public:
	MObject(){}
	virtual ~MObject(){}

	virtual void Start(){}
	virtual void Update() {}
	virtual void Render() {}

private:

};
