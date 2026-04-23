
function onAttach()
    print("attached")
end

function onUpdate(dt)
	local shouldMove = not isLeftMouseHeld()
	
    if getKey("a") and shouldMove then
		transform.x = transform.x - 10.0 * dt
    end
	
	if getKey("d") and shouldMove then
		transform.x = transform.x + 10.0 * dt
	end
	
	if getKey("w") and shouldMove then
		transform.y = transform.y + 10.0 * dt
	end
	
	if getKey("s") and shouldMove then
		transform.y = transform.y - 10.0 * dt
	end
end

function onDetach()
end