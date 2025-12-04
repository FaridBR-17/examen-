/***************************************************************
 * SISTEMA DE INVENTARIO - C++/Qt5/SQLite3
 * Archivo único con todo el código necesario
 * Compila en cualquier Linux con Qt5 instalado
 ***************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDebug>

// ============================================================================
// CLASE PRODUCTO - Modelo de datos
// ============================================================================
class Producto {
private:
    int id;
    QString nombre;
    QString descripcion;
    double precio;
    int cantidad;
    QString categoria;
    QDate fechaRegistro;

public:
    // Constructores
    Producto() : id(0), precio(0.0), cantidad(0), fechaRegistro(QDate::currentDate()) {}
    
    Producto(const QString& nom, const QString& desc, double prec, int cant, const QString& cat)
        : id(0), nombre(nom), descripcion(desc), precio(prec), cantidad(cant), 
          categoria(cat), fechaRegistro(QDate::currentDate()) {}

    // Getters
    int getId() const { return id; }
    QString getNombre() const { return nombre; }
    QString getDescripcion() const { return descripcion; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }
    QString getCategoria() const { return categoria; }
    QDate getFechaRegistro() const { return fechaRegistro; }

    // Setters
    void setId(int i) { id = i; }
    void setNombre(const QString& nom) { nombre = nom; }
    void setDescripcion(const QString& desc) { descripcion = desc; }
    void setPrecio(double prec) { precio = prec; }
    void setCantidad(int cant) { cantidad = cant; }
    void setCategoria(const QString& cat) { categoria = cat; }
    void setFechaRegistro(const QDate& fecha) { fechaRegistro = fecha; }

    // Validación
    bool esValido() const {
        return !nombre.isEmpty() && precio >= 0 && cantidad >= 0;
    }

    QString toString() const {
        return QString("ID: %1 - %2 - $%3 - Stock: %4")
            .arg(id).arg(nombre).arg(precio, 0, 'f', 2).arg(cantidad);
    }
};

// ============================================================================
// GESTOR DE BASE DE DATOS SQLite3
// ============================================================================
class GestorBD {
private:
    QSqlDatabase db;
    static GestorBD* instancia;

    GestorBD() {
        // Configurar conexión SQLite
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("inventario.db");  // Archivo en el mismo directorio
        
        if (!db.open()) {
            qDebug() << "ERROR BD:" << db.lastError().text();
            return;
        }
        
        crearTablas();
        insertarDatosIniciales();
    }

public:
    static GestorBD* getInstancia() {
        if (!instancia) {
            instancia = new GestorBD();
        }
        return instancia;
    }

    bool estaAbierta() const {
        return db.isOpen();
    }

    void crearTablas() {
        QSqlQuery query;
        
        // Tabla de productos
        bool ok = query.exec(
            "CREATE TABLE IF NOT EXISTS productos ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "codigo TEXT UNIQUE NOT NULL,"
            "nombre TEXT NOT NULL,"
            "descripcion TEXT,"
            "precio REAL NOT NULL CHECK(precio >= 0),"
            "cantidad INTEGER NOT NULL CHECK(cantidad >= 0),"
            "categoria TEXT,"
            "fecha_registro DATE DEFAULT CURRENT_DATE,"
            "activo BOOLEAN DEFAULT 1"
            ")"
        );
        
        if (!ok) {
            qDebug() << "Error creando tabla:" << query.lastError().text();
        }
        
        // Tabla de categorías
        query.exec(
            "CREATE TABLE IF NOT EXISTS categorias ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "nombre TEXT UNIQUE NOT NULL"
            ")"
        );
        
        // Índices para mejor rendimiento
        query.exec("CREATE INDEX IF NOT EXISTS idx_productos_nombre ON productos(nombre)");
        query.exec("CREATE INDEX IF NOT EXISTS idx_productos_categoria ON productos(categoria)");
    }

    void insertarDatosIniciales() {
        QSqlQuery query;
        
        // Verificar si ya hay datos
        query.exec("SELECT COUNT(*) FROM productos");
        if (query.next() && query.value(0).toInt() == 0) {
            // Insertar categorías
            query.exec("INSERT OR IGNORE INTO categorias (nombre) VALUES "
                      "('Electrónica'), ('Oficina'), ('Limpieza'), ('Alimentos')");
            
            // Insertar productos de ejemplo
            QStringList inserts = {
                "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
                "VALUES ('PROD-001', 'Mouse Inalámbrico', 'Mouse óptico USB', 25.99, 50, 'Electrónica')",
                
                "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
                "VALUES ('PROD-002', 'Teclado Mecánico', 'Teclado gaming RGB', 89.99, 30, 'Electrónica')",
                
                "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
                "VALUES ('PROD-003', 'Monitor 24\"', 'Monitor Full HD LED', 199.99, 15, 'Electrónica')",
                
                "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
                "VALUES ('PROD-004', 'Resma Papel A4', '500 hojas 75gr', 8.99, 200, 'Oficina')",
                
                "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
                "VALUES ('PROD-005', 'Lápices HB', 'Paquete de 12 lápices', 2.99, 300, 'Oficina')"
            };
            
            for (const QString& insert : inserts) {
                if (!query.exec(insert)) {
                    qDebug() << "Error insertando:" << query.lastError().text();
                }
            }
        }
    }

    // CRUD - Crear
    bool agregarProducto(const Producto& producto) {
        QSqlQuery query;
        query.prepare(
            "INSERT INTO productos (codigo, nombre, descripcion, precio, cantidad, categoria) "
            "VALUES (?, ?, ?, ?, ?, ?)"
        );
        
        // Generar código automático
        QString codigo = "PROD-" + QString::number(obtenerProximoId());
        
        query.addBindValue(codigo);
        query.addBindValue(producto.getNombre());
        query.addBindValue(producto.getDescripcion());
        query.addBindValue(producto.getPrecio());
        query.addBindValue(producto.getCantidad());
        query.addBindValue(producto.getCategoria());
        
        return query.exec();
    }

    // CRUD - Leer (todos)
    QList<Producto> obtenerProductos() {
        QList<Producto> lista;
        QSqlQuery query("SELECT id, codigo, nombre, descripcion, precio, cantidad, categoria, "
                       "fecha_registro FROM productos WHERE activo = 1 ORDER BY nombre");
        
        while (query.next()) {
            Producto p;
            p.setId(query.value(0).toInt());
            p.setNombre(query.value(2).toString());
            p.setDescripcion(query.value(3).toString());
            p.setPrecio(query.value(4).toDouble());
            p.setCantidad(query.value(5).toInt());
            p.setCategoria(query.value(6).toString());
            p.setFechaRegistro(query.value(7).toDate());
            lista.append(p);
        }
        
        return lista;
    }

    // CRUD - Leer (por ID)
    Producto obtenerProductoPorId(int id) {
        QSqlQuery query;
        query.prepare("SELECT id, nombre, descripcion, precio, cantidad, categoria "
                     "FROM productos WHERE id = ? AND activo = 1");
        query.addBindValue(id);
        
        if (query.exec() && query.next()) {
            Producto p;
            p.setId(query.value(0).toInt());
            p.setNombre(query.value(1).toString());
            p.setDescripcion(query.value(2).toString());
            p.setPrecio(query.value(3).toDouble());
            p.setCantidad(query.value(4).toInt());
            p.setCategoria(query.value(5).toString());
            return p;
        }
        
        return Producto();
    }

    // CRUD - Actualizar
    bool actualizarProducto(const Producto& producto) {
        QSqlQuery query;
        query.prepare(
            "UPDATE productos SET nombre = ?, descripcion = ?, precio = ?, "
            "cantidad = ?, categoria = ? WHERE id = ?"
        );
        
        query.addBindValue(producto.getNombre());
        query.addBindValue(producto.getDescripcion());
        query.addBindValue(producto.getPrecio());
        query.addBindValue(producto.getCantidad());
        query.addBindValue(producto.getCategoria());
        query.addBindValue(producto.getId());
        
        return query.exec();
    }

    // CRUD - Eliminar (soft delete)
    bool eliminarProducto(int id) {
        QSqlQuery query;
        query.prepare("UPDATE productos SET activo = 0 WHERE id = ?");
        query.addBindValue(id);
        return query.exec();
    }

    // Búsqueda
    QList<Producto> buscarProductos(const QString& termino) {
        QList<Producto> lista;
        QSqlQuery query;
        
        query.prepare(
            "SELECT id, nombre, descripcion, precio, cantidad, categoria "
            "FROM productos WHERE activo = 1 AND "
            "(nombre LIKE ? OR descripcion LIKE ? OR categoria LIKE ?) "
            "ORDER BY nombre"
        );
        
        QString likeTerm = "%" + termino + "%";
        query.addBindValue(likeTerm);
        query.addBindValue(likeTerm);
        query.addBindValue(likeTerm);
        
        if (query.exec()) {
            while (query.next()) {
                Producto p;
                p.setId(query.value(0).toInt());
                p.setNombre(query.value(1).toString());
                p.setDescripcion(query.value(2).toString());
                p.setPrecio(query.value(3).toDouble());
                p.setCantidad(query.value(4).toInt());
                p.setCategoria(query.value(5).toString());
                lista.append(p);
            }
        }
        
        return lista;
    }

    // Obtener categorías únicas
    QStringList obtenerCategorias() {
        QStringList categorias;
        QSqlQuery query("SELECT DISTINCT categoria FROM productos WHERE categoria IS NOT NULL ORDER BY categoria");
        
        while (query.next()) {
            categorias.append(query.value(0).toString());
        }
        
        if (categorias.isEmpty()) {
            categorias << "Electrónica" << "Oficina" << "Limpieza" << "Alimentos" << "Otros";
        }
        
        return categorias;
    }

    // Reporte de stock bajo
    QList<Producto> obtenerStockBajo(int limite = 10) {
        QList<Producto> lista;
        QSqlQuery query;
        query.prepare("SELECT id, nombre, descripcion, precio, cantidad, categoria "
                     "FROM productos WHERE activo = 1 AND cantidad <= ? ORDER BY cantidad");
        query.addBindValue(limite);
        
        if (query.exec()) {
            while (query.next()) {
                Producto p;
                p.setId(query.value(0).toInt());
                p.setNombre(query.value(1).toString());
                p.setDescripcion(query.value(2).toString());
                p.setPrecio(query.value(3).toDouble());
                p.setCantidad(query.value(4).toInt());
                p.setCategoria(query.value(5).toString());
                lista.append(p);
            }
        }
        
        return lista;
    }

    // Estadísticas
    QMap<QString, QVariant> obtenerEstadisticas() {
        QMap<QString, QVariant> stats;
        QSqlQuery query;
        
        // Total productos
        query.exec("SELECT COUNT(*) FROM productos WHERE activo = 1");
        if (query.next()) stats["total_productos"] = query.value(0);
        
        // Valor total del inventario
        query.exec("SELECT SUM(precio * cantidad) FROM productos WHERE activo = 1");
        if (query.next()) stats["valor_total"] = query.value(0).toDouble();
        
        // Productos con stock bajo
        query.exec("SELECT COUNT(*) FROM productos WHERE activo = 1 AND cantidad <= 10");
        if (query.next()) stats["stock_bajo"] = query.value(0);
        
        // Total categorías
        query.exec("SELECT COUNT(DISTINCT categoria) FROM productos WHERE activo = 1");
        if (query.next()) stats["total_categorias"] = query.value(0);
        
        return stats;
    }

private:
    int obtenerProximoId() {
        QSqlQuery query("SELECT MAX(id) FROM productos");
        if (query.next()) {
            return query.value(0).toInt() + 1;
        }
        return 1;
    }
};

// Inicializar instancia estática
GestorBD* GestorBD::instancia = nullptr;

// ============================================================================
// DIÁLOGO PARA AGREGAR/EDITAR PRODUCTO
// ============================================================================
class DialogoProducto : public QDialog {
    Q_OBJECT
public:
    DialogoProducto(QWidget* parent = nullptr, Producto* productoExistente = nullptr) 
        : QDialog(parent), producto(productoExistente) {
        
        setWindowTitle(producto ? "Editar Producto" : "Agregar Producto");
        setModal(true);
        resize(400, 300);
        
        // Crear widgets
        QFormLayout* layout = new QFormLayout(this);
        
        nombreEdit = new QLineEdit(this);
        descEdit = new QLineEdit(this);
        precioEdit = new QLineEdit(this);
        cantidadEdit = new QLineEdit(this);
        categoriaEdit = new QLineEdit(this);
        
        // Configurar placeholders
        nombreEdit->setPlaceholderText("Nombre del producto");
        descEdit->setPlaceholderText("Descripción opcional");
        precioEdit->setPlaceholderText("0.00");
        cantidadEdit->setPlaceholderText("0");
        categoriaEdit->setPlaceholderText("Categoría");
        
        // Agregar al layout
        layout->addRow("Nombre:*", nombreEdit);
        layout->addRow("Descripción:", descEdit);
        layout->addRow("Precio:*", precioEdit);
        layout->addRow("Cantidad:*", cantidadEdit);
        layout->addRow("Categoría:", categoriaEdit);
        
        // Botones
        QDialogButtonBox* buttonBox = new QDialogButtonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        layout->addRow(buttonBox);
        
        // Cargar datos si es edición
        if (producto) {
            nombreEdit->setText(producto->getNombre());
            descEdit->setText(producto->getDescripcion());
            precioEdit->setText(QString::number(producto->getPrecio(), 'f', 2));
            cantidadEdit->setText(QString::number(producto->getCantidad()));
            categoriaEdit->setText(producto->getCategoria());
        }
        
        // Conectar señales
        connect(buttonBox, &QDialogButtonBox::accepted, this, &DialogoProducto::validarYAcceptar);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }
    
    Producto getProducto() const {
        Producto p;
        p.setNombre(nombreEdit->text().trimmed());
        p.setDescripcion(descEdit->text().trimmed());
        p.setPrecio(precioEdit->text().toDouble());
        p.setCantidad(cantidadEdit->text().toInt());
        p.setCategoria(categoriaEdit->text().trimmed());
        return p;
    }

private slots:
    void validarYAcceptar() {
        // Validación básica
        if (nombreEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Validación", "El nombre es obligatorio");
            nombreEdit->setFocus();
            return;
        }
        
        bool okPrecio, okCantidad;
        double precio = precioEdit->text().toDouble(&okPrecio);
        int cantidad = cantidadEdit->text().toInt(&okCantidad);
        
        if (!okPrecio || precio < 0) {
            QMessageBox::warning(this, "Validación", "Precio inválido");
            precioEdit->setFocus();
            precioEdit->selectAll();
            return;
        }
        
        if (!okCantidad || cantidad < 0) {
            QMessageBox::warning(this, "Validación", "Cantidad inválida");
            cantidadEdit->setFocus();
            cantidadEdit->selectAll();
            return;
        }
        
        accept();
    }

private:
    QLineEdit* nombreEdit;
    QLineEdit* descEdit;
    QLineEdit* precioEdit;
    QLineEdit* cantidadEdit;
    QLineEdit* categoriaEdit;
    Producto* producto;
};

// ============================================================================
// VENTANA PRINCIPAL DE LA APLICACIÓN
// ============================================================================
class VentanaPrincipal : public QMainWindow {
    Q_OBJECT
public:
    VentanaPrincipal(QWidget* parent = nullptr) : QMainWindow(parent) {
        // Configurar ventana
        setWindowTitle("Sistema de Gestión de Inventario - C++/Qt5/SQLite3");
        setWindowIcon(QIcon());
        resize(900, 600);
        
        // Inicializar gestor BD
        gestorBD = GestorBD::getInstancia();
        if (!gestorBD->estaAbierta()) {
            QMessageBox::critical(this, "Error", "No se pudo conectar a la base de datos");
            QTimer::singleShot(0, qApp, &QApplication::quit);
            return;
        }
        
        // Crear widgets centrales
        crearMenu();
        crearWidgets();
        crearConexiones();
        
        // Cargar datos iniciales
        actualizarTabla();
        
        // Mostrar mensaje de bienvenida
        statusBar()->showMessage("Sistema listo. Productos cargados: " + 
                                QString::number(modelo->rowCount()), 3000);
    }

private slots:
    void agregarProducto() {
        DialogoProducto dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            Producto p = dialog.getProducto();
            if (gestorBD->agregarProducto(p)) {
                QMessageBox::information(this, "Éxito", "Producto agregado correctamente");
                actualizarTabla();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo agregar el producto");
            }
        }
    }
    
    void editarProducto() {
        QModelIndexList seleccionados = tabla->selectionModel()->selectedRows();
        if (seleccionados.isEmpty()) {
            QMessageBox::information(this, "Información", "Seleccione un producto para editar");
            return;
        }
        
        int fila = seleccionados.first().row();
        int id = modelo->item(fila, 0)->text().toInt();
        
        Producto p = gestorBD->obtenerProductoPorId(id);
        if (p.getId() == 0) {
            QMessageBox::warning(this, "Error", "No se pudo cargar el producto");
            return;
        }
        
        DialogoProducto dialog(this, &p);
        if (dialog.exec() == QDialog::Accepted) {
            Producto pEditado = dialog.getProducto();
            pEditado.setId(p.getId());
            
            if (gestorBD->actualizarProducto(pEditado)) {
                QMessageBox::information(this, "Éxito", "Producto actualizado");
                actualizarTabla();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo actualizar el producto");
            }
        }
    }
    
    void eliminarProducto() {
        QModelIndexList seleccionados = tabla->selectionModel()->selectedRows();
        if (seleccionados.isEmpty()) {
            QMessageBox::information(this, "Información", "Seleccione un producto para eliminar");
            return;
        }
        
        int fila = seleccionados.first().row();
        int id = modelo->item(fila, 0)->text().toInt();
        QString nombre = modelo->item(fila, 1)->text();
        
        if (QMessageBox::question(this, "Confirmar", 
            QString("¿Está seguro de eliminar el producto:\n\"%1\"?").arg(nombre),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            
            if (gestorBD->eliminarProducto(id)) {
                QMessageBox::information(this, "Éxito", "Producto eliminado");
                actualizarTabla();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo eliminar el producto");
            }
        }
    }
    
    void buscarProducto() {
        QString termino = buscarEdit->text().trimmed();
        if (termino.isEmpty()) {
            actualizarTabla();
            return;
        }
        
        QList<Producto> productos = gestorBD->buscarProductos(termino);
        cargarProductosEnTabla(productos);
        statusBar()->showMessage(QString("Búsqueda: %1 resultados").arg(productos.size()), 3000);
    }
    
    void mostrarEstadisticas() {
        auto stats = gestorBD->obtenerEstadisticas();
        
        QString mensaje = QString(
            "ESTADÍSTICAS DEL INVENTARIO\n\n"
            "Total productos: %1\n"
            "Valor total inventario: $%2\n"
            "Productos con stock bajo: %3\n"
            "Categorías diferentes: %4"
        ).arg(
            stats["total_productos"].toString(),
            QString::number(stats["valor_total"].toDouble(), 'f', 2),
            stats["stock_bajo"].toString(),
            stats["total_categorias"].toString()
        );
        
        QMessageBox::information(this, "Estadísticas", mensaje);
    }
    
    void mostrarAcercaDe() {
        QMessageBox::about(this, "Acerca de",
            "<h3>Sistema de Gestión de Inventario</h3>"
            "<p><b>Desarrollado en:</b> C++ con Qt5 y SQLite3</p>"
            "<p><b>Propósito:</b> Proyecto académico para gestión de inventario</p>"
            "<p><b>Características:</b></p>"
            "<ul>"
            "<li>CRUD completo de productos</li>"
            "<li>Búsqueda avanzada</li>"
            "<li>Reportes y estadísticas</li>"
            "<li>Base de datos embebida SQLite3</li>"
            "<li>Interfaz gráfica Qt5</li>"
            "</ul>"
            "<p><b>Requisitos:</b> Linux con Qt5 y SQLite3</p>");
    }
    
    void actualizarTabla() {
        QList<Producto> productos = gestorBD->obtenerProductos();
        cargarProductosEnTabla(productos);
        buscarEdit->clear();
        statusBar()->showMessage(QString("Productos cargados: %1").arg(productos.size()), 3000);
    }
    
    void exportarCSV() {
        QString nombreArchivo = QString("inventario_%1.csv").arg(QDate::currentDate().toString("yyyyMMdd"));
        
        QFile archivo(nombreArchivo);
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "No se pudo crear el archivo");
            return;
        }
        
        QTextStream out(&archivo);
        out.setCodec("UTF-8");
        
        // Encabezados
        out << "ID,Nombre,Descripción,Precio,Cantidad,Categoría,Fecha Registro\n";
        
        // Datos
        QList<Producto> productos = gestorBD->obtenerProductos();
        for (const Producto& p : productos) {
            out << p.getId() << ","
                << "\"" << p.getNombre() << "\","
                << "\"" << p.getDescripcion() << "\","
                << p.getPrecio() << ","
                << p.getCantidad() << ","
                << "\"" << p.getCategoria() << "\","
                << p.getFechaRegistro().toString("yyyy-MM-dd") << "\n";
        }
        
        archivo.close();
        QMessageBox::information(this, "Éxito", QString("Datos exportados a: %1").arg(nombreArchivo));
    }

private:
    void crearMenu() {
        // Menú Archivo
        QMenu* menuArchivo = menuBar()->addMenu("&Archivo");
        QAction* actExportar = new QAction("&Exportar a CSV", this);
        QAction* actSalir = new QAction("&Salir", this);
        menuArchivo->addAction(actExportar);
        menuArchivo->addSeparator();
        menuArchivo->addAction(actSalir);
        
        // Menú Productos
        QMenu* menuProductos = menuBar()->addMenu("&Productos");
        QAction* actAgregar = new QAction("&Agregar Producto", this);
        QAction* actEditar = new QAction("&Editar Producto", this);
        QAction* actEliminar = new QAction("&Eliminar Producto", this);
        QAction* actActualizar = new QAction("&Actualizar Lista", this);
        menuProductos->addAction(actAgregar);
        menuProductos->addAction(actEditar);
        menuProductos->addAction(actEliminar);
        menuProductos->addSeparator();
        menuProductos->addAction(actActualizar);
        
        // Menú Reportes
        QMenu* menuReportes = menuBar()->addMenu("&Reportes");
        QAction* actEstadisticas = new QAction("&Estadísticas", this);
        QAction* actStockBajo = new QAction("&Stock Bajo", this);
        menuReportes->addAction(actEstadisticas);
        menuReportes->addAction(actStockBajo);
        
        // Menú Ayuda
        QMenu* menuAyuda = menuBar()->addMenu("&Ayuda");
        QAction* actAcercaDe = new QAction("&Acerca de", this);
        menuAyuda->addAction(actAcercaDe);
        
        // Conectar acciones
        connect(actAgregar, &QAction::triggered, this, &VentanaPrincipal::agregarProducto);
        connect(actEditar, &QAction::triggered, this, &VentanaPrincipal::editarProducto);
        connect(actEliminar, &QAction::triggered, this, &VentanaPrincipal::eliminarProducto);
        connect(actActualizar, &QAction::triggered, this, &VentanaPrincipal::actualizarTabla);
        connect(actEstadisticas, &QAction::triggered, this, &VentanaPrincipal::mostrarEstadisticas);
        connect(actStockBajo, &QAction::triggered, this, []{
            auto productos = GestorBD::getInstancia()->obtenerStockBajo();
            QString mensaje;
            if (productos.isEmpty()) {
                mensaje = "¡Excelente! No hay productos con stock bajo.";
            } else {
                mensaje = "Productos con stock bajo:\n\n";
                for (const Producto& p : productos) {
                    mensaje += QString("• %1 (Stock: %2)\n").arg(p.getNombre()).arg(p.getCantidad());
                }
            }
            QMessageBox::information(nullptr, "Stock Bajo", mensaje);
        });
        connect(actExportar, &QAction::triggered, this, &VentanaPrincipal::exportarCSV);
        connect(actAcercaDe, &QAction::triggered, this, &VentanaPrincipal::mostrarAcercaDe);
        connect(actSalir, &QAction::triggered, qApp, &QApplication::quit);
    }
    
    void crearWidgets() {
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // Barra de búsqueda
        QHBoxLayout* searchLayout = new QHBoxLayout();
        buscarEdit = new QLineEdit(this);
        buscarEdit->setPlaceholderText("Buscar por nombre, descripción o categoría...");
        QPushButton* btnBuscar = new QPushButton("Buscar", this);
        QPushButton* btnLimpiar = new QPushButton("Limpiar", this);
        
        searchLayout->addWidget(new QLabel("Buscar:", this));
        searchLayout->addWidget(buscarEdit);
        searchLayout->addWidget(btnBuscar);
        searchLayout->addWidget(btnLimpiar);
        
        // Tabla de productos
        tabla = new QTableView(this);
        modelo = new QStandardItemModel(this);
        modelo->setHorizontalHeaderLabels({"ID", "Nombre", "Descripción", "Precio", "Cantidad", "Categoría", "Fecha Registro"});
        
        tabla->setModel(modelo);
        tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabla->setSelectionMode(QAbstractItemView::SingleSelection);
        tabla->setSortingEnabled(true);
        tabla->setAlternatingRowColors(true);
        
        // Ajustar columnas
        tabla->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        tabla->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        
        // Botones de acción
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        QPushButton* btnAgregar = new QPushButton("➕ Agregar", this);
        QPushButton* btnEditar = new QPushButton("✏️ Editar", this);
        QPushButton* btnEliminar = new QPushButton("🗑️ Eliminar", this);
        QPushButton* btnActualizar = new QPushButton("🔄 Actualizar", this);
        QPushButton* btnReportes = new QPushButton("📊 Reportes", this);
        
        buttonLayout->addWidget(btnAgregar);
        buttonLayout->addWidget(btnEditar);
        buttonLayout->addWidget(btnEliminar);
        buttonLayout->addWidget(btnActualizar);
        buttonLayout->addWidget(btnReportes);
        buttonLayout->addStretch();
        
        // Panel de estadísticas
        QHBoxLayout* statsLayout = new QHBoxLayout();
        lblTotalProductos = new QLabel("Total: 0", this);
        lblValorTotal = new QLabel("Valor: $0.00", this);
        lblStockBajo = new QLabel("Stock bajo: 0", this);
        
        statsLayout->addWidget(lblTotalProductos);
        statsLayout->addWidget(lblValorTotal);
        statsLayout->addWidget(lblStockBajo);
        statsLayout->addStretch();
        
        // Agregar al layout principal
        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(tabla);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addLayout(statsLayout);
        
        setCentralWidget(centralWidget);
        
        // Conectar botones
        connect(btnAgregar, &QPushButton::clicked, this, &VentanaPrincipal::agregarProducto);
        connect(btnEditar, &QPushButton::clicked, this, &VentanaPrincipal::editarProducto);
        connect(btnEliminar, &QPushButton::clicked, this, &VentanaPrincipal::eliminarProducto);
        connect(btnActualizar, &QPushButton::clicked, this, &VentanaPrincipal::actualizarTabla);
        connect(btnReportes, &QPushButton::clicked, this, &VentanaPrincipal::mostrarEstadisticas);
        connect(btnBuscar, &QPushButton::clicked, this, &VentanaPrincipal::buscarProducto);
        connect(btnLimpiar, &QPushButton::clicked, this, &VentanaPrincipal::actualizarTabla);
        connect(buscarEdit, &QLineEdit::returnPressed, this, &VentanaPrincipal::buscarProducto);
    }
    
    void crearConexiones() {
        // Conectar doble clic en tabla para editar
        connect(tabla, &QTableView::doubleClicked, this, &VentanaPrincipal::editarProducto);
    }
    
    void cargarProductosEnTabla(const QList<Producto>& productos) {
        modelo->removeRows(0, modelo->rowCount());
        
        for (const Producto& p : productos) {
            QList<QStandardItem*> fila;
            fila << new QStandardItem(QString::number(p.getId()));
            fila << new QStandardItem(p.getNombre());
            fila << new QStandardItem(p.getDescripcion());
            fila << new QStandardItem(QString::number(p.getPrecio(), 'f', 2));
            fila << new QStandardItem(QString::number(p.getCantidad()));
            fila << new QStandardItem(p.getCategoria());
            fila << new QStandardItem(p.getFechaRegistro().toString("dd/MM/yyyy"));
            
            // Color para stock bajo
            if (p.getCantidad() <= 10) {
                for (QStandardItem* item : fila) {
                    item->setBackground(QBrush(QColor(255, 200, 200)));
                }
            }
            
            modelo->appendRow(fila);
        }
        
        // Actualizar estadísticas
        actualizarEstadisticas();
    }
    
    void actualizarEstadisticas() {
        auto stats = gestorBD->obtenerEstadisticas();
        lblTotalProductos->setText(QString("Total productos: %1").arg(stats["total_productos"].toString()));
        lblValorTotal->setText(QString("Valor total: $%1").arg(
            QString::number(stats["valor_total"].toDouble(), 'f', 2)));
        lblStockBajo->setText(QString("Stock bajo: %1").arg(stats["stock_bajo"].toString()));
    }

private:
    GestorBD* gestorBD;
    QTableView* tabla;
    QStandardItemModel* modelo;
    QLineEdit* buscarEdit;
    QLabel* lblTotalProductos;
    QLabel* lblValorTotal;
    QLabel* lblStockBajo;
};

// ============================================================================
// FUNCIÓN PRINCIPAL
// ============================================================================
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Configurar aplicación
    app.setApplicationName("Sistema de Inventario");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Universidad");
    
    // Crear y mostrar ventana principal
    VentanaPrincipal ventana;
    ventana.show();
    
    return app.exec();
}

// Incluir archivo MOC para Q_OBJECT
#include "main.moc"