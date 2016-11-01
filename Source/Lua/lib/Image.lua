local Image = {
	Width = 200,
	Height = 200,
	should_sample = true,
	sampler = "MultiJittered",
	num_samples = 256,
	num_sets = 83
}

function Image:new(w, h)
	local instance = {}

	setmetatable(instance, self)
	self.__index = self

	self.width, self.height = w, h

	return instance
end

-- Sets the width and the height of the final rendered image.
function Image:SetSize(w, h)
	self.width, self.height = w, h
end

-- Sets the width of the final rendered image.
function Image:SetWidth(w)
	self.width = w
end

-- Sets the height of the final rendered image.
function Image:SetHeight(h)
	self.height = h
end

-- Sets if the image should be sampled for anti aliasing.
function Image:ShouldSample(flag)
	self.should_sample = flag
end

-- Sets which sampling technique to use (ignored if should_sample == false).
function Image:SetSampler(sampler)
	self.sampler = sampler
end

-- Sets the number of samples per pixel (ignored if should_sample == false).
function Image:SetNumSamples(num_samples)
	self.num_samples = num_samples
end

-- Sets the number of sets of samples per pixel (ignored if should_sample == false).
function Image:SetNumSets(num_sets)
	self.num_sets = num_sets
end

return Image