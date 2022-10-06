#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "shader.hpp"
#include "abstractMesh.hpp"
#include "transform.hpp"

using namespace std;

/**
 * @brief Enumeration de touche,
 * juste un wrapper moins verbeux que les defines de GLFW.
 */
enum Key
{
    ESCAPE = GLFW_KEY_ESCAPE,
    ARROW_DOWN = GLFW_KEY_DOWN,
    ARROW_UP = GLFW_KEY_UP,
    ARROW_LEFT = GLFW_KEY_LEFT,
    ARROW_RIGHT = GLFW_KEY_RIGHT
};

/**
 * @brief Classe de fenetre et de contexte OpenGL,
 * gere aussi les inputs.
 */
class Window
{
public:
    /////////////////////////////////////
    //// Constructeurs/Destructeurs. ////
    /////////////////////////////////////

    /**
     * @brief C'est un Constructeur de Fenêtre.
     * 
     * @param newTitle 
     * @param newWidth 
     * @param newHeight 
     */
    Window(const string& newTitle, unsigned int newWidth = 1920, unsigned int newHeight = 1080):
        width(newWidth),
        height(newHeight),
        title(newTitle),
        vsync(true)
    {
        initContext();
    }

    /**
     * @brief C'est un autre Constructeur de Fenêtre.
     * 
     * @param newWidth 
     * @param newHeight 
     * @param newTitle 
     */
    Window(unsigned int newWidth = 1920, unsigned int newHeight = 1080, const string& newTitle = "Default Title"):
        width(newWidth),
        height(newHeight),
        title(newTitle),
        vsync(true)
    {
        initContext();
    }

    Window(const Window& oth):
        width(oth.width),
        height(oth.height),
        title(oth.title),
        vsync(oth.vsync),
        window(oth.window)
    {
    }

    /**
     * @brief Détruit la fenêtre et termine proprement GLFW.
     */
    ~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

public:
    ////////////////////////////
    //// Accès aux données. ////
    ////////////////////////////

    /**
     * @brief Operateur de Cast pour utiliser la classe "Window" comme un "GLFWWIndow*".
     * 
     * @return GLFWwindow*
     */
    operator GLFWwindow*() const
    {
        return window;
    }

public:
    /////////////////////
    //// Accesseurs. ////
    /////////////////////

    /**
     * @brief Active ou non la VSync, peut etre chainer comme une Factorie.
     * 
     * @param enable 
     * @return Window& 
     */
    Window& setVSync(bool enable)
    {
        vsync = enable;
        return *this;
    }

    Window& setWireFrame(bool toggle = false) {
        if (toggle)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        return *this;
    }

    Window& setBackFaceCulling(bool toggle = false) {
        if (toggle)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
        return *this;
    }

public:
    /////////////////////////////////////////
    //// Fonctions Random du Pif (C FO). ////
    /////////////////////////////////////////

    /**
     * @brief Remet TOUT les Pixels de la Fenetre à la Couleur saisie.
     * 
     * @param r 
     * @param g 
     * @param b 
     * @param a 
     */
    void clear(float r = 0, float g = 0, float b = 0, float a = 0)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * @brief Récupération des événements sur la Fenêtre (clavier, souris, bouton fermer...) durant la frame par GLFW.
     * 
     */
    void pollEvents() const
    {
        glfwPollEvents();
    }

    /**
     * @brief Regarde si une Touche du clavier est Pressée durant la Frame.
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool isKeyDown(Key key) const
    {
        return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
    }

    /**
     * @brief Affiche la Nouvelle Frame dans la Fenêtre.
     */
    void display() const
    {
        glfwSwapBuffers(window);
        // Vsync, Attente du VBlank de l'écran (60 si écran 60Hz, 144 si 144Hz etc...).
        glfwSwapInterval(vsync);
    }

    /**
     * @brief Regarde si la Fenêtre est encore Ouverte.
     * 
     * @return true 
     * @return false 
     */
    bool isOpen() const
    {
        return !glfwWindowShouldClose(window);
    }

    /**
     * @brief Ferme la Fenêtre.
     */
    void closeWindow() const
    {
        glfwSetWindowShouldClose(window, true);
    }

    void draw(AbstractMesh& mesh, const Shader& shader, Transform& trans)
    {
        mesh.draw(shader, trans);
    }

private:
    ////////////////////////////
    //// Fonctions privées. ////
    ////////////////////////////

    /**
     * @brief Initialise le context OpenGL, crée une fenêtre de jeu et initialise d'autres extensions OpenGL.
     */
    void initContext()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!window)
        {
            cout << "Erreur initialisation fenêtre" << endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);
        glewInit();
    }

private:
    //////////////////
    //// Membres. ////
    //////////////////

    unsigned int width; //=> Largeur de la Fenetre.
    unsigned int height; //=> Hauteur de la Fenetre.
    string title; //=> Titre de la Fenetre.
    GLFWwindow *window; //=> Pointeur sur la Fenetre (Gerer par GLFW).
    bool vsync; //=> Flag pour activer ou non la VSync.
};

#endif // WINDOW_HPP