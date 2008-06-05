CREATE TABLE  unknown_packets(
    id SERIAL,
    componentcode SMALLINT NOT NULL,
    versioncode SMALLINT NOT NULL,
    contents BYTEA NOT NULL,  
    PRIMARY KEY (id)
);

CREATE TABLE gftp_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address INET,
    hostname VARCHAR(64) NOT NULL,
    gftp_version VARCHAR(64),
    stor_or_retr SMALLINT,
    start_time TIMESTAMP NOT NULL,
    end_time TIMESTAMP,
    num_bytes BIGINT,
    num_stripes INT,
    num_streams INT,
    buffer_size INT,
    block_size  INT,
    ftp_return_code INT,
    ip_version INT,
    loaded_dsi VARCHAR(64),
    event_modules TEXT,
    access_schema VARCHAR(16),
    client_app VARCHAR(128),
    client_appver VARCHAR(64),
    file_name TEXT,
    client_ip VARCHAR(64),
    data_ip VARCHAR(64),
    user_name VARCHAR(32),
    user_dn VARCHAR(128),
    conf_id TEXT,
    session_id VARCHAR(64),
    PRIMARY KEY (id)
);
-- To upgrade from previous version:
-- ALTER TABLE gftp_packets ADD loaded_dsi VARCHAR(64);
-- ALTER TABLE gftp_packets ADD event_modules TEXT;
-- ALTER TABLE gftp_packets ADD access_schema VARCHAR(16);
-- ALTER TABLE gftp_packets ADD client_app VARCHAR(128);
-- ALTER TABLE gftp_packets ADD client_appver VARCHAR(64);
-- ALTER TABLE gftp_packets ADD file_name TEXT;
-- ALTER TABLE gftp_packets ADD client_ip VARCHAR(64);
-- ALTER TABLE gftp_packets ADD data_ip VARCHAR(64);
-- ALTER TABLE gftp_packets ADD user_name VARCHAR(32);
-- ALTER TABLE gftp_packets ADD user_dn VARCHAR(128);
-- ALTER TABLE gftp_packets ADD conf_id TEXT;
-- ALTER TABLE gftp_packets ADD session_id VARCHAR(64);
-- and do the same for the mcs_internal_gftp_packets or whatever you
-- are using for gftp-filtered-out-table if applicable

CREATE TABLE rft_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    request_type SMALLINT NOT NULL,
    number_of_files BIGINT,
    number_of_bytes BIGINT,
    number_of_resources BIGINT,
    creation_time TIMESTAMP,
    factory_start_time TIMESTAMP,
    PRIMARY KEY (id)
);

CREATE TABLE gftp_summaries(
    id SERIAL,
    start_time BIGINT NOT NULL,
    end_time BIGINT NOT NULL,
    label VARCHAR(32), 
    num_transfers BIGINT,
    total_bytes BIGINT,
    num_hosts INT,
    avg_size BIGINT,
    avg_time BIGINT,
    avg_speed BIGINT,
    size_stddev DOUBLE PRECISION,
    time_stddev DOUBLE PRECISION,
    speed_stddev DOUBLE PRECISION,
    PRIMARY KEY (id)
);

CREATE TABLE java_ws_core_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    container_id INT,
    container_type SMALLINT,
    event_type SMALLINT,
    service_list TEXT,
    optional_val INT,
    version_major SMALLINT,
    version_minor SMALLINT,
    version_micro SMALLINT,
    port_number INT,
    thread_pool_size SMALLINT,
    thread_count SMALLINT,
    max_threads SMALLINT,
    threads_high_water_mark SMALLINT,
    service_request_count INT,
    jvm_info VARCHAR(64)
);

-- To upgrade from previous version:
-- ALTER TABLE java_ws_core_packets ADD version_major SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD version_minor SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD version_micro SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD port_number INT;
-- ALTER TABLE java_ws_core_packets ADD thread_pool_size SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD thread_count SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD max_threads SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD threads_high_water_mark SMALLINT;
-- ALTER TABLE java_ws_core_packets ADD service_request_count INT;
-- ALTER TABLE java_ws_core_packets ADD jvm_info VARCHAR(64);


CREATE TABLE gram_packets( 
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    creation_time TIMESTAMP,
    scheduler_type VARCHAR(20),
    job_credential_endpoint_used BOOLEAN,
    file_stage_in_used BOOLEAN,
    file_stage_out_used BOOLEAN,
    file_clean_up_used BOOLEAN,
    clean_up_hold_used BOOLEAN,
    job_type SMALLINT,
    gt2_error_code INT,
    fault_class SMALLINT,
    PRIMARY KEY(id)
);

CREATE TABLE c_ws_core_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    container_id INT,
    event_type SMALLINT,
    service_list TEXT
);

CREATE TABLE rls_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    rls_version VARCHAR(64),
    uptime BIGINT,
    lrc BOOLEAN,
    rli BOOLEAN,
    lfn INT,
    pfn INT,
    mappings INT,
    rli_lfns INT,
    rli_lrcs INT,
    rli_senders INT,
    rli_mappings INT,
    threads INT,
    connections INT,
    PRIMARY KEY(id)	
);

CREATE TABLE mpig_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    hostname VARCHAR(64),
    mpichver VARCHAR(20),
    start_time TIMESTAMP,
    end_time TIMESTAMP,
    nprocs INT,
    bytes_sent BIGINT,
    vendor_bytes_sent BIGINT,
    test INT,
    function_map TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE ogsadai_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    activity TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE mds_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    service_name VARCHAR(40),
    lifetime_reg_count INT,
    current_reg_count INT,
    resource_creation_time TIMESTAMP,
    PRIMARY KEY(id)
);

CREATE TABLE drs_packets(
    id SERIAL,
    component_code SMALLINT NOT NULL,
    version_code SMALLINT NOT NULL,
    send_time TIMESTAMP,
    ip_address VARCHAR(64) NOT NULL,
    number_of_files BIGINT,
    number_of_resources BIGINT,
    PRIMARY KEY (id)
);

CREATE TABLE graph_image_files(
    start_time TIMESTAMP,
    end_time TIMESTAMP,
    granularity INT,
    graph_type INT,
    graph_quant INT,
    filter VARCHAR(16),
    file_url TEXT
);
