Camera = {}

function Camera.new()
	local self = {}

	-- Public member variables
	self.eye = {x = 0.0, y = 0.0, z = 0.0}
	self.look_at = {x = 0.0, y = 0.0, z = -1.0}
	self.yaw = 5.0
	self.pitch = 0.0
	self.roll = 0.0
	self.exposure_time = 1.0
	
	-- Public methods
	function self.SetEye(x, y, z)
		eye.x, eye.y, eye.z = x, y, z
	end

	function self.LookAt(x, y, z)
		look_at.x, look_at.y, look_at.z = x, y, z
	end
	
	return self
end

return Camera