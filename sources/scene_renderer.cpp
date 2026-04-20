#include "scene_renderer.hpp"

#include "asset_manager.hpp"
#include "global.hpp"

#include <GL/gl3w.h>

static Frustum buildFrustum(const FPSCamera& camera) {
    Frustum frustum{};

    const float zFar  = 100.f;
    const float zNear = 0.1f;

    const float halfVSide        = zFar * tanf(camera.fov() * 0.5f);
    const float halfHSide        = halfVSide * camera.aspect();
    const glm::vec3 frontMultFar = zFar * camera.front();

    // clang-format off
    frustum.nearPlane = { camera.position() + zNear * camera.front(), camera.front() };
    frustum.farPlane = { camera.position() + frontMultFar, -camera.front() };
    frustum.topPlane = { camera.position(), glm::cross(frontMultFar - camera.up() * halfVSide, camera.right()) };
    frustum.bottomPlane = { camera.position(), glm::cross(camera.right(), frontMultFar + camera.up() * halfVSide) };
    frustum.rightPlane = { camera.position(), glm::cross(frontMultFar + camera.right() * halfHSide, camera.up()) };
    frustum.leftPlane = { camera.position(), glm::cross(camera.up(), frontMultFar - camera.right() * halfHSide) };
    // clang-format on

    return frustum;
}

static float getSignedDistance(const glm::vec3& point, const Plane& plane) {
    return glm::dot(plane.normal, point - plane.position);
}

static bool isInFront(const glm::mat4& transform, const CullingAABB& aabb, const Plane& plane) {
    auto position = transform * glm::vec4(aabb.center, 1);

    const float r = aabb.extents.x * std::abs(plane.normal.x) +
                    aabb.extents.y * std::abs(plane.normal.y) +
                    aabb.extents.z * std::abs(plane.normal.z);

    const float signedDistance = getSignedDistance(position, plane);

    return -r <= signedDistance;
}

static bool isInFrustum(
        const glm::mat4& transform,
        const CullingAABB& aabb,
        const Frustum& frustum
) {
    return isInFront(transform, aabb, frustum.nearPlane) &&
           isInFront(transform, aabb, frustum.farPlane) &&
           isInFront(transform, aabb, frustum.topPlane) &&
           isInFront(transform, aabb, frustum.bottomPlane) &&
           isInFront(transform, aabb, frustum.leftPlane) &&
           isInFront(transform, aabb, frustum.rightPlane);
}

SceneRenderer::SceneRenderer()
    : IRenderer(global.shadersPath, "scene") {}

SceneRenderer::SceneRenderer(const FPSCamera& camera, const Light& light)
    : IRenderer(global.shadersPath, "scene")
    , m_camera{&camera}
    , m_light{&light} {}

static glm::mat4 getTransform(const Scene& scene, int id) {
    if (!scene.getEntity(id)) {
        return glm::mat4(1.f);
    }

    auto transform = getTransform(scene, scene.getParent(id));

    return transform * scene.getEntity(id)->transform();
}

void SceneRenderer::draw(const IDrawable& drawable) const {
    // TODO: this might throw, in general shouldn't if everything is correctly set up
    const auto& scene = dynamic_cast<const Scene&>(drawable);

    Frustum frustum;
    if (m_camera) {
        frustum = buildFrustum(*m_camera);
    }

    m_program.use();

    m_program.setUniformLight(*m_light);
    m_program.setUniformCamera(*m_camera);

    for (const auto& entity: scene.entities()) {
        auto transform = getTransform(scene, entity.id);

        m_program.setUniformMat4("model", transform);

        auto* model = AssetManager::getModel(entity.modelId);
        if (model && isInFrustum(transform, model->aabb(), frustum)) {
            drawModelImpl(*model);
        }

        //if (model) {
        //    if (isInFrustum(transform, model->aabb(), frustum)) {
        //        drawModelImpl(*model);
        //    } else {
        //        std::cout << "Entity " << entity.id << " out of frustum\n";
        //    }
        //}
    }
}

void SceneRenderer::drawMeshImpl(const Mesh& mesh) const {
    glBindVertexArray(mesh.m_vao);
    glDrawElements(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void SceneRenderer::drawModelImpl(const Model& model) const {
    for (int i = 0; i < model.m_meshes.size(); i++) {
        auto materialId   = model.m_materials[i];
        auto materialData = AssetManager::getMaterial(materialId);

        materialData->bind();
        m_program.setUniformMaterial(*materialData);

        auto meshId   = model.m_meshes[i];
        auto meshData = AssetManager::getMesh(meshId);

        drawMeshImpl(*meshData);
    }
}