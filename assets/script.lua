
function onAttach()
    print("attached")
end

function onUpdate(dt)
    if getKey("a") then
		transform.x = transform.x + 10.0 * dt
    end
end

function onDetach()
end