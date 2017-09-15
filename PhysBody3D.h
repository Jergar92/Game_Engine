#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__



class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	btRigidBody* GetBody();
	void SetAsSensor(bool is_sensor);
private:
	btRigidBody* body = nullptr;
	bool is_sensor = false;

};

#endif // __PhysBody3D_H__