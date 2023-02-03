/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick3D 6.3
import FireParticles
import QtQuick3D.Particles3D 6.4

Rectangle {
    width: Constants.width
    height: Constants.height
    color: "#000000"


    View3D {
        id: view3D
        anchors.fill: parent

        environment: sceneEnvironment

        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
            }

            PerspectiveCamera {
                id: sceneCamera
                y: 35
                fieldOfView: 20
                z: 350
            }

            ParticleSystem3D {
                id: animatedSpriteSystem
                ParticleEmitter3D {
                    id: animatedSpriteEmitter
                    particleScale: 1.5
                    lifeSpanVariation: 100
                    particle: animatedSpriteParticle
                    lifeSpan: 2500
                    SpriteParticle3D {
                        id: animatedSpriteParticle
                        colorVariation.w: 0.5
                        blendMode: SpriteParticle3D.Screen
                        colorTable: fireColorTable
                        particleScale: 5
                        billboard: true
                        sprite: animatedTexture
                        spriteSequence: animatedSequence
                        SpriteSequence3D {
                            id: animatedSequence
                            randomStart: true
                            frameCount: 3
                            interpolate: true
                            duration: -1
                        }

                        Texture {
                            id: animatedTexture
                            source: "images/fire-sprites.png"
                        }

                        Texture {
                            id: fireColorTable
                            source: "images/fire-color-table.png"
                        }
                        maxAmount: 1000
                    }

                    VectorDirection3D {
                        id: animatedSpriteDirection
                        direction.y: 20
                        directionVariation.y: 10
                        directionVariation.x: 3
                    }
                    emitRate: 300
                    velocity: animatedSpriteDirection
                }
            }
        }
    }

    Item {
        id: __materialLibrary__
        DefaultMaterial {
            id: defaultMaterial
            objectName: "Default Material"
            diffuseColor: "#4aee45"
        }
    }
}
